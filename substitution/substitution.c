#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc!=2)
    {
        printf("enter 1 arguement \n");
        return 1;
    }

    string key=argv[1];

    if (strlen(key)!=26)
    {
        printf("enter 26 character key \n");
        return 1;
    }

    for(int i=0; i<26 ;i++)
    {
        key[i] = toupper(key[i]);
    }

    char diff[26];

    for(int i=0; i<26 ;i++)
    {
        diff[i]=key[i]-(65+i);
    }

    string plaintext=get_string("plaintext :  ");
    //string ciphertext=plaintext;

    for (int i=0, n=strlen(plaintext); i<n ; i++)
    {
        if (islower(plaintext[i]))
        {
            plaintext[i]=(int)diff[plaintext[i]-97]+plaintext[i];
        }
        if (isupper(plaintext[i]))
        {
            plaintext[i]=(int)diff[plaintext[i]-65]+plaintext[i];
        }
    }
    printf ("ciphertext : %s \n",plaintext);
    return 0;
}