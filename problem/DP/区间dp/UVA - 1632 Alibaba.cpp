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
#define inf 1000000000
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
int dp[maxn][maxn][2],x[maxn],d[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i = 0;i < n;++i)
            scanf("%d%d",&x[i],&d[i]);
        for(int i = 0;i < n;++i)
            dp[i][i][0] = dp[i][i][1] = 0;
        int j,tmp,tmp2;
        for(int i = n-1;i >= 0;--i)
            for(int j = i + 1;j < n;++j)
            {
                dp[i][j][0] = dp[i][j][1] = inf;
                tmp = min(dp[i+1][j][0] + x[i+1] - x[i],dp[i+1][j][1] + x[j] - x[i]);
                if(tmp < d[i] && tmp < dp[i][j][0])
                    dp[i][j][0] = tmp;
                tmp = min(dp[i][j-1][0] + x[j] - x[i],dp[i][j-1][1] + x[j] - x[j-1]);
                if(tmp < d[j] && tmp < dp[i][j][1])
                    dp[i][j][1] = tmp;
            }
        int ans = min(dp[0][n-1][0],dp[0][n-1][1]);
        if(ans == inf)
            puts("No solution");
        else
            printf("%d\n",ans);
    }
    return 0;
}
