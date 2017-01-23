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
const int maxn=55;
double dp[maxn][maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    int n,m,k,s,a,b;
    while(t--)
    {
        scanf("%d%d%d%d",&n,&m,&k,&s);
        memset(dp,0,sizeof(dp));
        dp[0][0][s]=1;
        for(int i=1;i<=m;++i)
        {
            dp[i][0][s]=1;
            scanf("%d%d",&a,&b);
            for(int j=1;j<=min(i,k);++j)
            {
                for(int x=1;x<=n;++x)
                {
                    if(x==a||x==b)
                        dp[i][j][x]+=dp[i-1][j-1][a==x?b:a];
                    else dp[i][j][x]+=dp[i-1][j-1][x];
                    dp[i][j][x]+=dp[i-1][j][x];
                }
            }
        }
        double maxv=-1;
        int ans;
        for(int i=1;i<=n;++i)
            if(maxv<dp[m][k][i])
            {
                maxv=dp[m][k][i];
                ans=i;
            }
        printf("%d\n",ans);
    }
    return 0;
}
