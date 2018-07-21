#include<stdio.h>
void sor(int*c)
{
    int x=0,y=0,temp;
    for(x=0;x<5;x++)
    {
        for(y=x+1;y<5;y++)
        {
            if((*(c+x))>(*(c+y)))
            {
                temp=*(c+x);
                *(c+x)=*(c+y);
                *(c+y)=temp;
            }
        }

    }
}
int check(int*d,int*e)
{
    int i=0,flag=1;
    for(i=0;i<5;i++)
    {
        if(*(d+i)!=*(e+i))
            flag=0;
    }
    return(flag);
}

void main()
{
    int a[5],b[5],i,j,r;
    printf("enter");

    for(i=0;i<5;i++)
    {
        scanf("%d",a+i);
    }
    printf("enter 2");
    for(i=0;i<5;i++)
    {
        scanf("%d",b+i);
    }
    sor(a);
    sor(b);
    r=check(a,b);
    printf("result %d",r);
}
