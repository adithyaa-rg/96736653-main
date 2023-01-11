#include<stdio.h>
#include<cs50.h>

void meow(int n);

int main(void)
{
    int n=get_int("Enter number of times to meow :");
    meow(n);
}

void meow(int n)
{
    for(int i = 0 ; i<n ; i++)
    {
        printf("meow \n");
    }
}