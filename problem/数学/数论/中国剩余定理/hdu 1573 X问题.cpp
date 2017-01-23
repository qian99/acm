#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll a[20],r[20];
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b;
}
ll solve(int n,int m)
{
    for(int i=0;i<m;++i)
        cin>>a[i];
    for(int i=0;i<m;++i)
        cin>>r[i];
    ll x,aa,A,B,C,d,xx,yy;
    x=r[0],aa=a[0];
    bool flag=true;
    for(int i=1;i<m;++i)
    {
        A=aa,B=a[i],C=r[i]-x;
        d=ext_gcd(A,B,xx,yy);
        if(C%d!=0)
        {
            flag=false;
            break;
        }
        xx*=(C/d);B/=d;
        xx=(xx%B+B)%B;
        x=x+xx*aa;
        aa=lcm(aa,a[i]);
    }
    if(!flag) return 0;
    if(n<x) return 0;
    n-=x;
    if(x!=0) return n/aa+1;
    return n/aa;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        cout<<solve(n,m)<<endl;
    }
    return 0;
}
