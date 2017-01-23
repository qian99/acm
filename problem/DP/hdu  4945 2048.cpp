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
const int maxn = 2048+10;
const int maxm = 100000+10;
const int mod = 998244353;
int cnt[15],convert[maxn],mx[15];
ll dp[15][maxn];
ll p[maxm],pinv[maxm],pw[maxm];
ll pow_mod(ll x,ll n)
{
    ll res = 1;
    while(n)
    {
        if(n&1) res = res * x %mod;
        x = x * x %mod;
        n >>= 1;
    }
    return res;
}
ll inv(ll x)
{
    return pow_mod(x,mod-2);
}
inline void Update(ll & a,ll b)
{
    a += b;
    if(a >= mod) a -= mod;
}
inline ll C(ll n,ll m)
{
    return p[n]*pinv[m]%mod*pinv[n-m]%mod;
}
void reads(int & x)
{
    char c;
    bool neg=false;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')
    {
        neg=true;
        while((c=getchar())<'0'||c>'9');
    }
    x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';
    if(neg) x=-x;
}
void create()
{
    int n;
    int tcase = 20;
    while(tcase--)
    {
        int m =0;// rand()%20;
        n = m + rand()%10 + 10;
        printf("%d\n",n);
        for(int i = 1;i <= m;++i)
        {
            int val = rand()%2049;
            printf("%d ",val);
        }
        for(int i = m + 1;i <= n;++i)
        {
            int val = pw[rand()%11];
            printf("%d ",val);
        }
        printf("\n\n");
    }
    printf("0\n");
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    pw[0] = 1;
    for(int i = 1;i <maxm;++i)
        pw[i] = pw[i-1]*2%mod;
    ////////////////////////////////////
//    create();
//    if(1) return 0;
    ///////////////////////////////
    p[0] = 1;pinv[0] = 1;
    for(int i = 1;i < maxm;++i)
    {
        p[i] = p[i-1] * i %mod;
        pinv[i] = inv(p[i]);
    }
    int tmp = 1;
    memset(convert,0,sizeof(convert));
    for(int i = 1; tmp < maxn ;++i)
    {
        convert[tmp] = i;
        tmp *= 2;
    }
    mx[1] = 2048;
    mx[0] = 0;
    for(int i = 2;i < 15;++i)
        mx[i] = mx[i-1]/2;
    int n,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        int a ;
        memset(cnt,0,sizeof(cnt));
        for(int i = 0;i < n;++i)
        {
            reads(a);
            cnt[convert[a]]++;
        }
        ll v;
        ll sum;
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        int ww;
        for(int i = 1;i <= 11;++i)
        {
            for(int j = 0;j <= mx[i-1];++j)
                Update(dp[i][j>>1],dp[i-1][j]);
            sum = 0;
            ww = min(mx[i],cnt[i]);
            for(int j = 1;j <= ww;++j)
            {
                v = C(cnt[i],j)%mod;
                Update(sum,v);
                for(int k = 0;k <= mx[i-1];++k)
                {
                    if(dp[i-1][k])
                    Update(dp[i][min((k>>1)+j,mx[i])],v*dp[i-1][k]%mod);
                }
            }
            if(cnt[i] > mx[i])
            {
                v = (pw[cnt[i]] - sum - 1)%mod;
                v = (v + mod)%mod;
                for(int k = 0;k <= mx[i-1];++k)
                    Update(dp[i][mx[i]],v*dp[i-1][k]%mod);
            }
        }
        ll ans = 0;
        for(int i = 2;i <= mx[11];++i)
            Update(ans,dp[11][i]);
        if(cnt[12])
        {
            v = pw[cnt[12]] - 1;
            v = v*pw[n-cnt[12]-cnt[0]]%mod;
            v = (v%mod + mod)%mod;
            Update(ans,v);
        }
        if(cnt[0])
        {
            v =pw[cnt[0]];
            ans = ans * v %mod;
        }
        ans = (ans%mod +mod) %mod;
        printf("Case #%d: %I64d\n",++tcase,ans);
    }
    return 0;
}
