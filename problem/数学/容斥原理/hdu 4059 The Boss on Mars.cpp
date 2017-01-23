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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
const int mod = 1e9 + 7;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt = 0;
    for(int i = 2;i < maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++] = i;
            for(int j = i*i;j < maxn;j += i)
                flag[j] = true;
        }
    }
}
ll pow_mod(ll x,ll n)
{
    ll res = 1;
    while(n)
    {
        if(n & 1) res = res*x%mod;
        x = x*x%mod;
        n >>= 1;
    }
    return res;
}
int factor[maxn],cnt[maxn],tot;
ll ans;
inline ll POW4(ll x)
{
    return x*x%mod*x%mod*x%mod;
}
ll SUM(ll n)
{
    ll ans;
    ans = n*(n + 1)%mod*(2*n + 1)%mod*(3*n*n%mod + 3*n%mod - 1)%mod;
    ans = ans*pow_mod(30,mod - 2)%mod;
    ans = (ans%mod + mod)%mod;
    return ans;
}
void getfactor(int n)
{
    tot = 0;
    for(int i = 0;i < pcnt && n >= primes[i];++i)
    {
        if(n % primes[i] == 0)
        {
            factor[tot] = primes[i];
            cnt[tot] = 0;
            while(n % primes[i] == 0) { n /= primes[i];cnt[tot]++; }
            tot++;
        }
    }
    if(n > 1) { factor[tot] = n; cnt[tot++] = 1;}
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    getprimes();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll n;
        scanf("%I64d",&n);
        ans = 0;
        getfactor(n);
        for(int i = 0; i < (1<<tot);++i)
        {
            int tmp = 1,x = 0;
            for(int j = 0;j < tot;++j)
                if(i & (1<<j))
                    tmp *= factor[j],x++;
            if(x & 1)
            {
                ans -= SUM(n/tmp)*POW4(tmp)%mod;
                ans = (ans%mod + mod)%mod;
            }
            else
            {
                ans += SUM(n/tmp)*POW4(tmp)%mod;
                ans = (ans%mod + mod)%mod;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

