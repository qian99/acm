#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
ll solve(double xx1,double yy1,double xx2,double yy2)
{
    ll x1,y1,x2,y2;
    x1=(xx1)*10;
    y1=(yy1)*10;
    x2=(xx2)*10;
    y2=(yy2)*10;
    if(x1==x2)
    {
        if(x1%10) return 0;
        if(yy2<yy1) swap(yy1,yy2);
        y1=ceil(yy1);y2=floor(yy2);
        return max(y2-y1+1,0LL);
    }
    if(y1==y2)
    {
        if(y1%10) return 0;
        if(xx2<xx1) swap(xx1,xx2);
        x1=ceil(xx1);x2=floor(xx2);
        return max(x2-x1+1,0LL);
    }
    ll a=(y2-y1)*10,b=(x1-x2)*10,c=x1*y2-x2*y1;
    ll x,y,d,k1=0;
    if(yy2<yy1) swap(yy1,yy2);
        y1=ceil(yy1);y2=floor(yy2);
    if(xx2<xx1) swap(xx1,xx2);
        x1=ceil(xx1);x2=floor(xx2);
    if(y1>y2||x1>x2) return 0;
    d=ext_gcd(a,b,x,y);
    if(c%d!=0) return 0;
    a/=d;b/=d;
    x*=(c/d);y*=(c/d);
    if(b<0) b=-b;
    x=x-(x-x1)/b*b;
    x-=b;
    while(x<x1) x+=b;
    k1=(x2-x)/b;
    while(x+k1*b<=x2) k1++;
    return k1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double x1,y1,x2,y2;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        ll ans=solve(x1,y1,x2,y2);
        printf("%lld\n",ans);
    }
    return 0;
}
