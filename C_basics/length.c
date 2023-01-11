#include<stdio.h>
#include<cs50.h>
#include<string.h>

int string_len(string s);

int main(void)
{
    string name=get_string("Enter your name: ");
    int length=string_len(name);
    printf("Length is %d \n",length);
    printf("Length is %li \n",strlen(name));

}

int string_len(string s)
{
    int i=0;
    while(s[i]!='\0')
    {
        i+=1;
    }
    return i;
}