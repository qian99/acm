#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
int lf[maxn][maxn],ups[maxn][maxn];
int dp[maxn][maxn][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(dp,0,sizeof(dp));
        memset(lf,0,sizeof(lf));
        memset(ups,0,sizeof(ups));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&lf[i][j]);
                lf[i][j]+=lf[i][j-1];
            }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&ups[i][j]);
                ups[i][j]+=ups[i-1][j];
            }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                dp[i][j][0]=lf[i][j]+max(dp[i-1][j][0],ups[i-1][j]+max(dp[i-1][j-1][0],dp[i-1][j-1][1]));
                dp[i][j][1]=ups[i][j]+max(dp[i][j-1][1],lf[i][j-1]+max(dp[i-1][j-1][0],dp[i-1][j-1][1]));
            }
        }
        int ans=max(dp[n][m][0],dp[n][m][1]);
        printf("%d\n",ans);
    }
    return 0;
}
