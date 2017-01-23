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
ll a[55],r[55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>n;
        for(int i=0;i<n;++i)
            cin>>a[i];
        for(int j=0;j<n;++j)
            cin>>r[j];
        ll x,aa,A,B,C,d,xx,yy;
        x=r[0],aa=a[0];
        bool flag=true;
        for(int i=1;i<n;++i)
        {
            A=aa,B=a[i],C=r[i]-x;
            d=ext_gcd(A,B,xx,yy);
            if(C%d) {flag=false;break;}
            B/=d;
            xx*=C/d;
            xx=(xx%B+B)%B;
            x=x+aa*xx;
            aa=lcm(a[i],aa);
        }
        if(!flag) x=-1;
        if(x==0) x=aa;
        cout<<"Case "<<tcase<<": "<<x<<endl;
    }
    return 0;
}
