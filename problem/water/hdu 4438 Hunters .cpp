#include <iostream>
#include<cstdio>
#include<memory.h>
#include<math.h>
using namespace std;
int main()
{
    //freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int x,y;
        double p,q;
        double a,b;
        scanf("%d%d%lf%lf",&x,&y,&p,&q);
        a=q*(p*x+p*y)+(1-q)*x;
        b=y*q+(1-q)*(p*y+p*x);
        if(a>b)
          printf("tiger %.4lf\n",a);
        else
          printf("wolf %.4lf\n",b);
    }
    return 0;
}
