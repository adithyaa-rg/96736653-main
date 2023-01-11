#include<stdio.h>
#include<string.h>
#include<cs50.h>

int main()
{
    string name=get_string("Enter your name : ");
    for(int i = 0 , n = strlen(name) ; i<n ; i++ )
    {
        name[i]=name[i]+1;
    }

    printf("Name is %s \n",name);
}