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
const int maxn=40000+10;
int primes[maxn],pcnt,mod;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=(ll)i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
int euler_phi(int x)
{
    int ans=x;
    for(int i=0;(ll)primes[i]*primes[i]<=x;++i)
    {
        if(x%primes[i]==0)
        {
            ans=ans-ans/primes[i];
            while(x%primes[i]==0) x/=primes[i];
        }
    }
    if(x>1) ans=ans-ans/x;
    return ans%mod;
}
ll pow_mod(ll x,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
int factor[110],cnt[110],tot;
ll ans;
void dfs(int x,int now,int n)
{
    if(x==tot)
    {
        ans=ans+pow_mod(n,now-1)*euler_phi(n/now)%mod;
        ans%=mod;
        return ;
    }
    int tmp=1;
    for(int i=0;i<=cnt[x];++i)
    {
        dfs(x+1,now*tmp,n);
        tmp*=factor[x];
    }
}
void solve(int n)
{
    int N=n;
    tot=0;
    for(int i=0;(ll)primes[i]*primes[i]<=N;++i)
    {
        if(N%primes[i]==0)
        {
            factor[tot]=primes[i];
            cnt[tot]=0;
            while(N%primes[i]==0) {cnt[tot]++;N/=primes[i];}
            tot++;
        }
    }
    if(N>1) {factor[tot]=N;cnt[tot++]=1;}
    ans=0;
    dfs(0,1,n);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d%d",&n,&mod);
        solve(n);
        printf("%lld\n",ans);
    }
    return 0;
}
