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
const int maxn = 200 + 10;
int dp[maxn][55],t[55];
int hastrain[maxn][55][2];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,T,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        scanf("%d",&T);
        memset(hastrain,0,sizeof(hastrain));
        for(int i = 1;i < n;++i)
            scanf("%d",&t[i]);
        int m,d;
        scanf("%d",&m);
        for(int i = 0;i < m;++i)
        {
            scanf("%d",&d);
            for(int j = 1;j <= n;++j)
            {
                hastrain[d][j][0] = 1;
                d += t[j];
                if(d > T) break;
            }
        }
        scanf("%d",&m);
        for(int i = 0;i < m;++i)
        {
            scanf("%d",&d);
            for(int j = n; j >= 1;--j)
            {
                hastrain[d][j][1] = 1;
                d += t[j-1];
                if(d > T) break;
            }
        }
        memset(dp,0x3f,sizeof(dp));
        dp[T][n] = 0;
        for(int i = T - 1;i >= 0;--i)
        {
            for(int j = 1;j <= n;++j)
            {
                dp[i][j] = min(dp[i][j],dp[i+1][j] + 1);
                if(hastrain[i][j][0] && i + t[j] <= T && j < n)
                    dp[i][j] = min(dp[i][j],dp[i + t[j]][j+1]);
                if(hastrain[i][j][1] && i + t[j-1] <= T && j > 1)
                    dp[i][j] = min(dp[i][j],dp[i+t[j-1]][j-1]);
            }
        }
        int ans = dp[0][1];
        printf("Case Number %d: ",++tcase);
        if(ans == inf) printf("impossible\n");
        else printf("%d\n",ans);
    }
    return 0;
}
