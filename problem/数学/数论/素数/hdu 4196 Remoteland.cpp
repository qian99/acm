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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000000+10;
const int mod=1000000007;
int primes[maxn],pcnt;
bool flag[maxn];
ll fac[maxn];
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
    fac[0]=1;
    for(int i=1;i<maxn;++i)
        fac[i]=fac[i-1]*i%mod;
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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        ll ans=1,x,d=1;
        for(int i=0;i<pcnt&&primes[i]<=n;++i)
        {
            x=n;
            int cnt=0;
            while(x)
            {
                cnt+=x/primes[i];
                x/=primes[i];
            }
            if(cnt&1) d=d*primes[i]%mod;
        }
        ans=fac[n]*pow_mod(d,mod-2)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
