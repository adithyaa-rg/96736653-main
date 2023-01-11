#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for(int i=0,n=strlen(argv[1]); i<n ; i++)
    {
        if (isdigit(argv[1][i])==0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int length = atoi(argv[1]);
    length=length%26;
    string plaintext=get_string("Plaintext =  ");
    for (int i=0, n=strlen(plaintext); i<n ; i++)
    {
        if(isupper(plaintext[i]))
        {
            if (((int) plaintext[i]-64+length)>26)
            {
                plaintext[i]=plaintext[i]+(length-26);
            }
            else
            {
                plaintext[i]=plaintext[i]+length;
            }
        }
        else if(islower(plaintext[i]))
        {
            if (((int) plaintext[i]-96+length)>26)
            {
                plaintext[i]=plaintext[i]+(length-26);
            }
            else
            {
                plaintext[i]=plaintext[i]+length;
            }
        }
    }
    printf("ciphertext =  %s \n",plaintext);
    return 0;

}
