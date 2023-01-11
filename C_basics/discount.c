#include<stdio.h>
#include<cs50.h>

float sale(float price, float discount);

int main(void){
    float discount;
    float price=get_float("Enter the price of the item :");
    do{
        discount=get_float("Enter discount value :");
    }
    while (discount < 0 || discount > 100);

    float sale_price=sale(price,discount);
    printf("sale price is %.2f \n",sale_price);
}

float sale(float price, float discount){
    return price*(1-discount/100);
}