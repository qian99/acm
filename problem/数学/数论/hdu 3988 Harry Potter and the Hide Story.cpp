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
typedef unsigned long long ull;
const int maxn = 10000000 + 10;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    pcnt = 0;
    for(ll i = 2;i < maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++] = i;
            for(ll j = i*i; j < maxn;j += i)
                flag[j] = true;
        }
    }
}
ll factor[110];
int tot;
void getfactor(ll n)
{
    tot = 0;
    for(int i = 0;i < pcnt && primes[i] <= n;++i)
    {
        if(n % primes[i] == 0)
        {
            factor[tot++] = primes[i];
            while(n % primes[i] == 0) n /= primes[i];
        }
    }
    if(n > 1) factor[tot++] = n;
}
ll getval(ll x,ll p)
{
    ll mul = p,sum = 0;
    while(mul <= x)
    {
        sum += x/mul;
        if(mul > (double)x/p) break;
        mul *= p;
    }
    return sum;
}
ll getcnt(ll x,ll p)
{
    ll res = 0;
    while(x%p == 0)
    {
        res++;
        x /= p;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    getprimes();
    int t,tcase = 0;
    ll n,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%I64d%I64d\n",&n,&k);
        printf("Case %d: ",++tcase);
        if(k == 1)
        {
            puts("inf");
            continue;
        }
        getfactor(k);
        ll ans = -1,x;
        for(int i = 0;i < tot;++i)
        {
            x = getval(n,factor[i])/getcnt(k,factor[i]);
            if(ans == -1)
                ans = x;
            else
                ans = min(ans,x);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
