import os
import datetime
import math
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

QUOTE=[]
# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
#db.execute("delete from quotes")
# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    lookups=[]
    data_1=db.execute("SELECT symbol,sum(shares) 'shares' FROM user_shares  WHERE user_id=? GROUP BY symbol",session["user_id"])
    data_2=db.execute("SELECT cash FROM users WHERE id=?",session["user_id"])[0]
    for symbol in data_1:
        lookups+=[lookup(symbol["symbol"])]
    cash_inhand=float(data_2["cash"])
    cash_inhand=round(cash_inhand,2)
    cash_investment=0
    for i in range(len(data_1)):
        cash_investment+=(int(data_1[i]["shares"])*float(lookups[i]['price']))
    total=cash_inhand+cash_investment
    total=round(total,2)
    return render_template("index.html",data_1=data_1,data_2=cash_inhand,current_prices=lookups,length=len(data_1),total=total)
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method=="POST":
        symbol=request.form.get("symbol")
        shares=int(request.form.get("shares"))

        if shares<0:
            return apology("enter positive number of shares",403)

        user_id=db.execute("select username from users where id=?",session["user_id"])[0]
        quote=lookup(symbol)
        user_data=db.execute("select * from users where username=?",user_id["username"])
        if(float(quote["price"])*shares>float(user_data[0]["cash"])):
            return apology("You can't afford these many shares")
        db.execute("UPDATE users SET cash=? where username=?",float(user_data[0]["cash"])-shares*float(quote["price"]),user_id["username"])

        now = datetime.datetime.now()
        date=now.strftime("%Y/%m/%d %H:%M:%S")
        db.execute("INSERT INTO transactions VALUES(?,?,?,?,?)",user_id["username"],symbol,shares,float(quote["price"])*shares,date)
        db.execute("INSERT INTO user_shares VALUES(?,?,?)",session["user_id"],symbol,shares)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id=db.execute("select username from users where id=?",session["user_id"])[0]
    user_data=db.execute("select * from transactions where username=?",user_id["username"])
    return render_template("history.html",quotes=user_data)
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    db.execute("DELETE FROM quotes")
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    db.execute("DELETE FROM quotes")
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required

def quote():
    if request.method=="POST":
        symbol=request.form.get("symbol")
        QUOTE=lookup(symbol)
        db.execute("INSERT INTO quotes(name,price,symbol) VALUES(?,?,?)",QUOTE["name"],QUOTE["price"],QUOTE["symbol"])
        quotes=db.execute("SELECT * FROM quotes")
        return render_template("quoted.html",quotes=quotes)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method=="POST":
        username=request.form.get("username")
        password=generate_password_hash(request.form.get("password"))
        if not username:
            return apology("must provide username", 403)
        if not (request.form.get("password")):
            return apology("must provide paddword", 403)
        db.execute("INSERT INTO users(username,hash) VALUES(?,?)",username,password)
        return redirect('/register')
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks=db.execute("SELECT DISTINCT symbol,sum(shares) 'shares' FROM user_shares where user_id=? GROUP BY symbol",session["user_id"])
    if request.method=="GET":

        max_shares=db.execute("SELECT sum(shares) 'shares' from user_shares where user_id=? GROUP BY symbol",session["user_id"])
        max=[]
        for i in max_shares:
            max+=[int(i["shares"])]
        max_share=max[0]
        for i in max:
            if i>max_share:
                max_share=i
        return render_template("sell.html",stocks=stocks,max_shares=max_share)

    else:
        symbol=request.form.get("symbol")
        shares=request.form.get("shares")
        if not symbol:
            return apology("enter choose symbol",403)
        if not shares:
            return apology("enter shares",403)
        if int(shares)<0:
            return apology("enter positive number",403)
        available_shares=-1
        for stock in stocks:
            if symbol.lower()==stock["symbol"].lower():
                available_shares=int(stock["shares"])
                break
        if available_shares<int(shares):
            return apology("enter shares available",403)
        user_id=db.execute("select username from users where id=?",session["user_id"])[0]
        quote=lookup(symbol)
        now = datetime.datetime.now()
        date=now.strftime("%Y/%m/%d %H:%M:%S")
        db.execute("INSERT INTO transactions VALUES(?,?,?,?,?)",user_id["username"],symbol,shares,-float(quote["price"])*int(shares),date)
        db.execute("INSERT INTO user_shares VALUES(?,?,?)",session["user_id"],symbol,-int(shares))
        return redirect("/")
    #return apology("TODO")
