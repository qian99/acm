//A->D B->C 两条路径不相交的方案数： AD*BC - AC*BD(看做相交后走到对方的终点)
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
const int mod=100000007;
const int maxn=200000+10;
ll fact[maxn];
void Init()
{
    fact[1]=1;
    for(int i=2;i<maxn;++i)
        fact[i]=fact[i-1]*i%mod;
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
ll inv(ll n)
{
    ll x,y;
    ext_gcd(n,mod,x,y);
    return (x%mod+mod)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m,p,q;
    ll ans,ans2,tmp;
    Init();
    while(cin>>m>>n>>p>>q)
    {
        p=m-p;
        ans=fact[m+n]*fact[p+q]%mod;
        tmp=fact[n]*fact[m]%mod;
        tmp=tmp*(fact[p]*fact[q]%mod)%mod;
        ans=ans*inv(tmp)%mod;
        ans2=fact[m+q]*fact[n+p]%mod;
        ans2=ans2*inv(tmp)%mod;
        ans=ans-ans2;
        ans=(ans%mod+mod)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
