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
const int maxn = 100 + 10;
int a[maxn][maxn],dp[maxn][maxn],path[maxn][maxn],ans[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase = 0,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= m;++j)
                scanf("%d",&a[i][j]);
        for(int i = 1;i <= m;++i)
            dp[1][i] = a[1][i];
        for(int i = 2;i <= n;++i)
        {
            for(int j = 1;j <= m;++j)
            {
                dp[i][j] = inf;
                if(j + 1 <= m)
                {
                    dp[i][j] = dp[i - 1][j + 1] + a[i][j];
                    path[i][j] = j + 1;
                }
                if(dp[i - 1][j] + a[i][j] < dp[i][j])
                {
                    dp[i][j] = dp[i - 1][j] + a[i][j];
                    path[i][j] = j;
                }
                if(j - 1 > 0 && dp[i - 1][j - 1] + a[i][j] < dp[i][j])
                {
                    dp[i][j] = dp[i - 1][j - 1] + a[i][j];
                    path[i][j] = j - 1;
                }
            }
        }
        int p = m;
        for(int i = m;i >= 1;--i)
            if(dp[n][i] < dp[n][p])
                p = i;
        ans[n] = p;
        for(int i = n;i > 1;--i)
        {
            ans[i - 1] = path[i][p];
            p = path[i][p];
        }
        printf("Case %d\n",++tcase);
        printf("%d",ans[1]);
        for(int i = 2;i <= n;++i)
            printf(" %d",ans[i]);
        puts("");
    }
    return 0;
}
