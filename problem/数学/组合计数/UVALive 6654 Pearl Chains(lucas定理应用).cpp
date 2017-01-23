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
const int mod = 1000003;
ll f[mod + 10],fX[mod + 10],fY[mod + 10],fZ[mod + 10],inv[mod + 10];
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
inline ll C(int n,int m)
{
    return f[n]*inv[f[m]]%mod*inv[f[n - m]]%mod;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    f[0] = 1;inv[0] = 1;
    for(int i = 1;i <= mod;++i)
    {
        f[i] = f[i-1]*i%mod;
        inv[i] = pow_mod(i,mod - 2);
    }
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll A,B,X,Y,Z;
        scanf("%lld%lld%lld%lld%lld",&A,&B,&X,&Y,&Z);
        X %= mod; Y %= mod; Z %= mod;
        fX[0] = fY[0] = fZ[0] = 1;
        for(int i = 1;i < mod;++i)
        {
            fX[i] = fX[i-1]*X%mod;
            fY[i] = fY[i-1]*Y%mod;
            fZ[i] = fZ[i-1]*Z%mod;
        }
        ll ans = 1,sum;
        while(A && B)
        {
            int a = A%mod,b = B%mod;
            int n = min(a,b);
            sum = 0;
            for(int i = 0;i <= n;++i)
            {
                sum += C(a + b - i,a - i)*C(b,b - i)%mod*fX[a - i]%mod*fY[b - i]%mod*fZ[i]%mod;
                sum %= mod;
            }
            ans = ans*sum%mod;
            A /= mod; B /= mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

