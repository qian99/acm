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
const int maxn = 1000 + 10;
double p[15][maxn];
double dp[maxn][1<<10];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i = 0;i <= m;++i)
            for(int j = 0;j < (1<<n);++j)
                dp[i][j] = -1;
        for(int i = 0;i < n;++i)
            for(int j = 1;j <= m;++j)
                scanf("%lf",&p[i][j]);
        dp[0][0] = 0;
        for(int i = 0;i < m;++i)
        {
            for(int j = 0;j < (1<<n);++j)
            {
                if(dp[i][j] < 0) continue;
                if(j == (1<<n) - 1)
                {
                    for(int k = 0;k < n;++k)
                        dp[i+1][1<<k] = max(dp[i+1][1<<k],dp[i][j] + p[k][i+1]);
                    continue;
                }
                for(int k = 0;k < n;++k)
                {
                    if(j & (1<<k)) continue;
                    dp[i+1][j|(1<<k)] = max(dp[i+1][j|(1<<k)],dp[i][j] + p[k][i+1]);
                }
            }
        }
        double ans = 0;
        for(int i = 0;i < (1<<n);++i)
            ans = max(ans,dp[m][i]);
        printf("Case #%d: %.5lf\n",++tcase,ans);
    }
    return 0;
}