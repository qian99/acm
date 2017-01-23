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
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
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
ll lcm(ll x,ll y)
{
    return x/gcd(x,y)*y;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,r,x,la,k,y,A,B,C,d;
    int n;
    while(cin>>n)
    {
        cin>>a>>r;
        x=r;
        la=a;
        bool flag=true;
        for(int i=1;i<n;++i)
        {
            cin>>a>>r;
            if(!flag) continue;
            A=la;B=a;C=r-x;
            d=ext_gcd(A,B,k,y);
            if(C%d!=0) {flag=false; continue;}
            C/=d;B/=d;
            k*=C;
            k=(k%B+B)%B;
            x=x+la*k;
            la=lcm(la,a);
        }
        if(!flag) x=-1;
        cout<<x<<endl;
    }
    return 0;
}
