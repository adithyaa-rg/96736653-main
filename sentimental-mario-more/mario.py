while True:
    try:
        height = int(input("Height: "))
        if height>0:
            for i in range(height):
                print(" "*(height-1-i)+"#"*(i+1)+" "+"#"*(i+1))
            break
    except ValueError:
        print("Enter an integer")

