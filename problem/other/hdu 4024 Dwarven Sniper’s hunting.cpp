#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
struct Point
{
    double x,y;
};
double getLen(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double x1,y1,x2,y2,lx,ly,vD,vB,L;
    while(~scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&lx,&ly,&vD,&vB,&L))
    {
        if(x1==0&&y1==0&&x2==0&&y2==0&&lx==0&&ly==0&&vD==0&&vB==0&&L==0) { break;}
        double l=0,r=1e9;
        double t;
        Point a,b;
        a.x=x2;a.y=y2;
        double r1,r2,len;
        while(r-l>eps)
        {
            t=(l+r)/2;
            b.x=x1+t*lx;
            b.y=y1+t*ly;
            r1=vD*(t-L/vB);
            r2=L;
            len=getLen(a,b);
            if(r2>len+r1)
               l=t;
            else if(r1>len+r2)
               r=t;
            else if(len>r1+r2)
               l=t;
            else
               r=t;
        }
        printf("%.3lf %.3lf\n",L,l);
    }
    return 0;
}
