import math
while True:
    try:
        cash = float(input("Change owed: "))*100
        cash=int(cash)
        if cash>0:
            coins_quarters=cash // 25
            cash=cash-25*coins_quarters
            
            coins_dimes=cash//10
            cash=cash-coins_dimes*10

            coins_nickle=cash//5
            cash=cash-coins_nickle*5

            coins_pennies=cash

            print(coins_pennies+coins_nickle+coins_dimes+coins_quarters)
            break

    except ValueError:
        print("enter floats")