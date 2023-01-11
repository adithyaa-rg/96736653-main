card_number = input("Number: ")
length=len(card_number)
if 13<=length<=16:
    sum=0
    try:
        for i in range(-1,-length-1,-1):
            if (i%2==1):
                sum+=int(card_number[i])
            else:
                tem=int(card_number[i])*2
                if(tem//10==0):
                    sum+=tem
                else:
                    sum+=(tem%10+tem//10)
        if sum%10==0:
            if (card_number[0]=="3" and card_number[1] in "47" and length==15):
                print("American Express")
            elif (length==16 and card_number[0]=="5" and card_number[1] in "12345"):
                print("MASTERCARD")
            elif ((length==16 or length==13) and card_number[0]=="4"):
                print("VISA")
        else:
            print("INVALID")
    except ValueError:
        print("Wrong Entry")
else:
    print("INVALID")