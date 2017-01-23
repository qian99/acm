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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 10;
ll gcd(ll a,ll b) { return b == 0 ? a : gcd(b,a%b);}
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
        }
        for(ll j = 0;j < pcnt;++j)
        {
            if(i*primes[j] > maxn) break;
            flag[i*primes[j]] = true;
            if(i % primes[j] == 0) break;
        }
    }
}
ll factor[100010],res[100010];
int cnt[100010];
int tot,m;
map<ll,int>mp;
void dfs(int pos,ll val)
{
    if(pos == tot)
    {
        if(mp.find(val) != mp.end()) return ;
        mp[val] = 1;
        res[m++] = val;
        return ;
    }
    ll tmp = 1;
    for(int i = 0;i <= cnt[pos];++i)
    {
        dfs(pos + 1,val*tmp);
        tmp *= factor[pos];
    }
}
void getfactor(ll n)
{
    ll N = n;
    tot = 0;
    for(int i = 0;i < pcnt && N >= primes[i];++i)
    {
        if(N % primes[i] == 0)
        {
            factor[tot] = primes[i];
            cnt[tot] = 0;
            while(N % primes[i] == 0) { cnt[tot]++;N /= primes[i];}
            tot++;
        }
    }
    if(N > 1) {factor[tot] = N; cnt[tot++] = 1;}
    mp.clear();
    m = 0;
    dfs(0,1);
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
        ll x,y,K;
        scanf("%I64d%I64d%I64d\n",&x,&y,&K);
        ll n = gcd(x,y);
        getfactor(n);
        sort(res,res + m);
        if(m < K)
            puts("-1");
        else
            printf("%I64d\n",res[m - K]);
    }
    return 0;
}