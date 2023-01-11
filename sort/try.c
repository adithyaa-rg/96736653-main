#include<stdio.h>
#include<stdlib.h>
void merge_sort(int *x,int l, int u);
void merge(int *x, int l, int u, int m);
int main()
{
    int a[]={5,6,3,2,8,9,0};
    merge_sort(a,0,6);
    for(int i=0; i<7 ; i++)
    {
        printf("%d\n",a[i]);
    }
}
void merge(int *x, int l, int u, int m)
{
    int *y=malloc(sizeof(x));
    int *z=malloc(sizeof(x));
    int len= sizeof(*
    x)/sizeof(x[0]);

    for (int i=0;i<u;i++)
    {
        if (i<=m)
        {
        y[i]=x[i];
        }

    }

    for (int i=0;i<u;i++)
    {
        if (m+1+i<=u)
        {
        z[i]=x[m+1+i];
        }

    }
    int n=l;
    int i=0,j=0;

    while (i<m-l+1 && j<u-m)
    {
        if (y[i]>z[j])
        {
            x[n]=z[j];
            j+=1;
        }
        else if (y[i]<z[j])
        {
            x[n]=y[i];
            i+=1;
        }
        n+=1;
    }
     while (i < m-l+1) {
        x[n] = y[i];
        i++;
        n++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < u-m) {
        x[n] = z[j];
        j++;
        n++;
    }


}

void merge_sort(int *x,int l, int u)
{
    if (l<u)
    {
    int m=(l+u)/2;
    merge_sort(x,l,m);
    merge_sort(x+m,m+1,u);

    merge(x,l,u,m);
    }
}