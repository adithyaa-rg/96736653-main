#include<stdio.h>
#include<cs50.h>
#include<string.h>
int main()
{
    string name=get_string("Enter your name : ");

    for(int i=0,n=strlen(name);i<n;i++)
    {
        if( name[i] >= 'a' && name[i] <= 'z' )
        {
            name[i]=name[i]-32;
        }
        else if ( name[i] >= 'A' && name[i] <= 'Z' )
        {
            name[i]=name[i]+32;
        }
        else
        {
            name[i]=name[i];
        }
    }

    printf("Swapcase : %s\n",name);
}
