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
const int maxn = 20;
double dp[maxn][1<<16],f[1<<16],sum[maxn][1<<20],pk[maxn][maxn],g[1<<16];
double p[maxn],h[maxn][maxn];
int cnt[1<<16],pos[1<<16],m,n;
void Init()
{
    for(int i = 0;i < 16;++i)
        pos[1<<i] = i;
    for(int i = 0;i < (1<<16);++i)
    {
        cnt[i] = 0;
        int x = i;
        while(x)
        {
            cnt[i]++;
            x = x & (x-1);
        }
    }
}
double solve()
{
    for(int i = 1;i <= n;++i)
        for(int j = 0;j < (1<<m);++j)
        {
            dp[i][j] = 0;
            sum[i][j] = 0;
            for(int k = 0;k < m;++k)
                if(j & (1<<k))
                    sum[i][j] += h[k][i];
        }
    double res = 0;
    for(int i = 0;i < m;++i)
    {
        pk[i][1] = 1.0;
        res += h[i][1];
        for(int j = 2;j <= n;++j)
        {
            pk[i][j] = pk[i][j-1]*p[i];
            res += pk[i][j]*h[i][j];
        }
    }
    for(int i = 1;i <= n;++i)
    {
        for(int j = 0;j < (1<<m);++j)
        {
            dp[i][j] = 1.0;
            for(int k = 0;k < m;++k)
                if(j & (1<<k))
                    dp[i][j] *= pk[k][i];
                else
                    dp[i][j] *= (1 - pk[k][i]);
        }
    }
    for(int i = 1;i < n;++i)
    {
        for(int j = 1;j < (1<<m);++j)
            f[j] = dp[i][j]/cnt[j];
        f[0] = 0;
        for(int j = 0;j < m;++j)
            for(int k = 0;k < (1<<m);++k)
            {
                if(k & (1<<j))
                {
                    f[k^(1<<j)] += f[k]*(1 - p[j]);
                    f[k] *= p[j];
                }
            }
        f[0] = 0;
        for(int j = 0;j < (1<<m);++j)
            res += sum[i+1][j]*f[j]*cnt[j];
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    while(~scanf("%d%d",&m,&n))
    {
        for(int i = 0;i < m;++i)
            scanf("%lf",&p[i]);
        for(int i = 0;i < m;++i)
            for(int j = 1;j <= n;++j)
                scanf("%lf",&h[i][j]);
        double ans = solve();
        printf("%.10lf\n",ans);
    }
    return 0;
}
