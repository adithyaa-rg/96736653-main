#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do{
    n=get_int("Enter the number of levels :");
    }
    while (n<1 || n>8);
    //Main for loop for each line
    for (int i=1; i<=n ; i++){

        // Loop to print the initial spaces
        for(int j=0 ; j<(n-i); j++){
            printf(" ");
        }

        // Printing the hash pattern
        for(int j=0 ; j<i ; j++){
            printf("#");
        }
        printf(" ");

        // Printing the hash pattern again
        for(int j=0 ; j<i ; j++){
            printf("#");
        }
        printf("\n");
    }
}