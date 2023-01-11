#include <stdio.h>
#include <cs50.h>

int main()
{
    int i=0;
    int search[]={1,2,3,4,5,6,7};
    int l=0;
    int u=6;
    int m=(l-u)/2;
    while (l<u)
    {
        if (search[m]==1)
        {
            printf("present");
            return 0;
        }
        else if (search[m]>1)
        {
            u=m;
            m=l+(u-l)/2;
            printf("%d-%d\n",m,i);
        }
        else
        {
            l=m;
            m=m+(u-l)/2+1;
            printf("%d-%d\n",m,i);
        }
        i++;
    }
}
