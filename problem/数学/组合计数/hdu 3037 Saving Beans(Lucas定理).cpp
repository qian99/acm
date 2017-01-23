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
ll pow_mod(ll x,ll n,ll m)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%m;
        x=x*x%m;
        n>>=1;
    }
    return res;
}
ll cal(ll n,ll m,ll p)
{
    ll x=1,y=1;
    for(ll i=1;i<=m;++i)
    {
        x=x*(n-i+1)%p;
        y=y*i%p;
    }
    return x*pow_mod(y,p-2,p)%p;
}
ll Lucas(ll n,ll m,ll p)
{
    if(n<m) return 0;
    ll x,y,ans=1;
    while(n&&m&&ans)
    {
        x=n%p;y=m%p;
        n/=p;m/=p;
        ans=ans*cal(x,y,p)%p;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m,p;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>p;
        cout<<Lucas(n+m,m,p)<<endl;
    }
    return 0;
}
