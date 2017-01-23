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
const int maxn = 200000 + 10;
const int mod = 1e9 + 7;
ll pw[maxn];
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
inline ll inv(ll x)
{
    return pow_mod(x,mod - 2);
}
inline ll C(int n,int m)
{
    return pw[n]*inv(pw[m])%mod*inv(pw[n-m])%mod;
}
ll cal(int n,int m,int g)
{
    if(g == 1)
    {
        if(n == 0 && m == 1)
            return 1;
        if(n <= 0) return 0;
        return cal(n-1,m,0);
    }
    else
    {
        if(n == 1 && m == 0)
            return 1;
        ll res = 0;
        if(m > 0 && n + m > 1)
            res += C(m - 1 + n,n);
        if(n > 0)
        {
            res += cal(n-1,m,1);
        }
        return res%mod;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    pw[0] = 1;
    for(int i = 1;i < maxn;++i)
        pw[i] = pw[i-1]*i%mod;
    int n,m,g;
    scanf("%d%d%d",&n,&m,&g);
    ll ans = cal(n,m,g);
    ans = (ans%mod + mod)%mod;
    printf("%I64d\n",ans);
    return 0;
}