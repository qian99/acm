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
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=(a/b)*x;
    return d;
}
void cal(ll x,ll y,ll b,ll &k1,ll &k2)
{
    if(b<0)
    {
        x=-x;y=-y;b=-b;
        swap(x,y);
    }
    if(x<=0) k1=x/b;
    else k1=(x-1)/b+1;
    if(y>=0) k2=y/b;
    else k2=(y+1)/b-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b,c,x1,x2,y1,y2;
    cin>>a>>b>>c>>x1>>x2>>y1>>y2;
    c=-c;
    ll ans=0,tmp;
    if(a==0&&b==0)
    {
        if(!c) ans=(x2-x1+1)*(y2-y1+1);
    }
    else if(a==0)
    {
        if(c%b==0)
        {
            tmp=c/b;
            if(tmp>=y1&&tmp<=y2) ans=1;
        }
    }
    else if(b==0)
    {
        if(c%a==0)
        {
            tmp=c/a;
            if(tmp>=x1&&tmp<=x2) ans=1;
        }
    }
    else
    {
        ll x,y;
        ll d=ext_gcd(a,b,x,y);
        if(c%d==0)
        {
            ll k1,k2,k3,k4;
            cal(x1-x*(c/d),x2-x*(c/d),b/d,k1,k2);
            cal(y1-y*(c/d),y2-y*(c/d),-a/d,k3,k4);
            ans=min(k2,k4)-max(k1,k3)+1;
            if(ans<0) ans=0;
        }
    }
    cout<<ans<<endl;
    return 0;
}
