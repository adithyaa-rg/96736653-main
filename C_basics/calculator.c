#include<cs50.h>
#include<stdio.h>

int main(void){
    //Input the number
    int num_1=get_int("Enter number 1 ");
    int num_2=get_int("Enter number 2 ");

    //Adding the numbers
    int sum = num_1 + num_2 ;

    //Subtract the numbers
    int diff = num_1 - num_2 ;

    //Product of the numbers
    int prod = num_1 * num_2 ;

    //Division of the numbers
    float div = float(num_1) / float(num_2) ;

    //Print the sum,diff,prod,div
    printf("sum is %d \n",sum);
    printf("diff is %d \n",diff);
    printf("prof is %d \n",prod);
    printf("div is %f \n",div);

}