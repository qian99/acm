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
ll factor[110],minv;
int cnt[110],tot;
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b);}
ll euler_phi(ll n)
{
    ll ans=n;
    ll m=sqrt(n+0.5);
    for(ll i=2;i<=m;++i)
    {
        if(n%i==0)
        {
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans=ans-ans/n;
    return ans;
}
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
void dfs(int pos,ll now,ll n)
{
    if(pos==tot)
    {
        ll tmp=pow_mod(2,now,n);
        if(tmp==1)
            minv=min(now,minv);
        return ;
    }
    if(now>minv) return ;
    ll tmp=1;
    for(int i=0;i<=cnt[pos];++i)
    {
        dfs(pos+1,now*tmp,n);
        tmp*=factor[pos];
    }
}
ll solve(ll n,ll M)
{
    ll tmp=n;
    ll m=sqrt(n+0.5);
    tot=0;
    memset(cnt,0,sizeof(cnt));
    for(ll i=2;i<=m;++i)
    {
        if(tmp%i==0)
        {
            factor[tot]=i;
            while(tmp%i==0) {tmp/=i;cnt[tot]++;}
            tot++;
        }
    }
    if(tmp>1) {factor[tot]=tmp;cnt[tot++]=1;}
    minv=n;
    dfs(0,1,M);
    return minv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll p,q;
    int tcase=0;
    while(~scanf("%I64d/%I64d",&p,&q))
    {
        printf("Case #%d: ",++tcase);
        if(p==0)
        {
            printf("0 0\n");
            continue;
        }
        ll d=gcd(p,q);
        p/=d;q/=d;
        ll a=0,b;
        while(q%2==0) {a++;q/=2;}
        b=solve(euler_phi(q),q);
        printf("%I64d,%I64d\n",a+1,b);
    }
    return 0;
}
