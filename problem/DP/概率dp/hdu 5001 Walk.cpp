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
const int maxn = 55;
const int maxm = 10000 + 10;
double dp[2][maxn][maxn];
double ans[maxn];
int g[maxn][maxn],cnt[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,d;
        scanf("%d%d%d",&n,&m,&d);
        memset(g,0,sizeof(g));
        memset(cnt,0,sizeof(cnt));
        int u,v;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            g[u][v] = g[v][u] = 1;
            cnt[u]++;
            cnt[v]++;
        }
        memset(dp,0,sizeof(dp));
        for(int i = 1;i <= n;++i)
        {
            for(int j = 1;j <= n;++j)
                dp[0][i][j] = 1.0/n;
            dp[0][i][i] = 0;
        }
        int p;
        for(int i = 0;i < d;++i)
        {
            p = i & 1;
            memset(dp[p^1],0,sizeof(dp[p^1]));
            for(int j = 1;j <= n;++j)
                for(int k = 1;k <= n;++k)
                {
                    for(int x = 1; x <= n;++x)
                    {
                        if(g[j][x])
                        {
                            if(k != x)
                                dp[p^1][x][k] += dp[p][j][k]*1.0/cnt[j];
                        }
                    }
                }
        }

        memset(ans,0,sizeof(ans));
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                ans[i] += dp[d&1][j][i];
        for(int i = 1;i <= n;++i)
            printf("%.10lf\n",ans[i]);
    }
    return 0;
}
