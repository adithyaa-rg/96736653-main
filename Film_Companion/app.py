import requests

import os
from datetime import datetime
import math
from cs50 import SQL
from flask import Flask, flash, redirect, render_template,request,session,jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required
QUOTE=[]
# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///movies.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    #db.execute("DELETE FROM quotes")
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
        if len(rows) != 1 or not check_password_hash(rows[0]["password"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/register", methods=["POST","GET"])
def register():
    """Register a user"""
    if request.method=="POST":
        username=request.form.get("username")
        if not username:
            return apology("enter username",403)
        password=request.form.get("password")
        if not password:
            return apology("enter password",403)
        email=request.form.get("email")
        if not email:
            return apology("enter password",403)
        password_hash=generate_password_hash(password)
        count=int(db.execute("select count(id) from users")[0]["count(id)"])
        db.execute("INSERT INTO users VALUES(?,?,?,?)",count+1,username,password_hash,email)
        return redirect('/login')
    else:
        return render_template("register.html")

@app.route("/")
def index():#change the css and make index as search
    return render_template("index.html")


@app.route("/search")
def search():#change css to make it look nicer and probably make it a button which can be clicked and takes to a new page
    q = request.args.get("q")
    if q:
        shows = db.execute("SELECT * FROM movies WHERE title LIKE ? LIMIT 50", "%" + q + "%")
    else:
        shows = []
    return jsonify(shows)
#<a href="/movies?mov_id='shows[id]["id"]'">
def get_movie_description(title):
        api_key = "cce0928b"
        api_url = "http://www.omdbapi.com/?apikey=" + api_key + "&t=" + title
        response = requests.get(api_url)
        data = response.json()
        #print(data)
        return data['Plot'],data['Poster']

@app.route("/movies",methods=["GET","POST"])
@login_required
def movies():#ideally make it a select button and use ID to get the movie name and remaining stuff here
    mov_id=request.args.get("mov_id")
    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    stars= request.form.get('star')
    db.execute("INSERT INTO ratings_user VALUES(?,?,?,?)",mov_id,session["user_id"],dt_string,stars)
    #if request.method=="get":
    movie=db.execute("SELECT title FROM movies WHERE id=?",mov_id)[0]["title"]
    cast=db.execute("SELECT name FROM people,movies,stars WHERE movies.id=stars.movie_id AND stars.person_id=people.id AND movies.id=?",mov_id)
    year=db.execute("SELECT year FROM movies WHERE title=?",movie)
    director=db.execute("SELECT name FROM people,movies,directors WHERE movies.id=directors.movie_id AND directors.person_id=people.id AND movies.title=?",movie)

    description,poster = get_movie_description(movie)

    ###average current rating-use a new database with each entry and then narrow out movie id and avg out the score
    #for user score use like interactive stars maybe use js(half triangle as options and based on rating changing correspondingly) try googling
    #if rating is rerating check for that entry using database and rechange it.
    #also get a link for image or something
    return render_template("movies.html",movie=movie,cast=cast,year=year,director=director,desc=description,poster=poster)
    #else:


'''@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    db.execute("DELETE FROM quotes")
    session.clear()

    # Redirect user to login form
    return redirect("/")
'''