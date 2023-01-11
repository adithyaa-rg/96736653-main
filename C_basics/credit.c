#include <cs50.h>
#include <stdio.h>

long get_input();

int main(void)
{
    long card_no=0;
    do{
    card_no=get_input();
    }
    while (card_no<0);


    long last_digit=card_no;
    int n=0;
    int odd_sum=0,even_sum=0;

    //verification algorithm
    while(card_no!=0)
    {
    int new_sum=0;
    int temp=0;

        if(n%2==0)
        {
            odd_sum+=card_no%10;
        }
        else
        {
            temp=(card_no%10)*2;

            if(temp%10!=temp)
            {
                new_sum=temp%10+1;
            }
            else
            {
                new_sum=temp;
            }
            even_sum+=new_sum;
        }

        last_digit=card_no;
        card_no=(card_no-card_no%10)/10;
        n+=1;
    }


    int validity=(even_sum+odd_sum)%10;

    //size validity checker
    if (validity==0){
        printf("VALID\n");
    }
    else{
        printf("INVALID\n");
    }

    //trying classification of brands
    if (13<=n && n<=16)
    {
        if (last_digit==4)
        {
            printf("VISA\n");
        }
        else if (last_digit==3)
        {
            printf("AMERICAN EXPRESS\n");
        }
        else if (last_digit==5)
        {
            printf("MASTERCARD\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }
}

long get_input()
{
    long card_no=get_long("Enter your card number(13-16 digits)");
    return card_no;
}