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
const int maxn = 1000 + 10;
int dp[maxn][maxn],hp[maxn],c[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m = 0;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&hp[i]);
            m = max(hp[i],m);
        }
        sort(hp + 1,hp + n + 1);
        memset(c,0,sizeof(c));
        memset(dp,0xff,sizeof(dp));
        for(int i = 1;i <= n;++i)
        {
            for(int j = hp[i];j >= 1;--j)
                if(!c[j])
                {
                    c[j] = hp[i];
                    break;
                }
        }
        dp[0][0] = 0;
        for(int i = 1;i <= m;++i)
            for(int j = 0;j <= i;++j)
            {
                if(j > 0) dp[i][j] = dp[i-1][j-1];
                if(!c[i]) continue;
                int x = j + c[i] - i;
                if(x >= 0 && dp[i-1][x] != -1)
                    dp[i][j] = max(dp[i][j],dp[i-1][x] + 1);
            }
        int ans = 0;
        for(int i = 0;i <= m;++i)
            ans = max(ans,dp[m][i]);
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}
