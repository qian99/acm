//dp[i][j][k]表示前i列巧克力分为j块时，第i列的两块巧克力是分开或者在一起时的分法总数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
using namespace std;
const int maxn=1000+10;
const int mod=100000007;
int dp[maxn][maxn<<1][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    dp[1][1][0]=dp[1][2][1]=1;
    for(int i=2;i<=1000;++i)
    {
        for(int j=1;j<=(i-1)*2;++j)
        {
            dp[i][j+2][1]=(dp[i][j+2][1]+dp[i-1][j][0]+dp[i-1][j][1])%mod;
            dp[i][j+1][1]=(dp[i][j+1][1]+dp[i-1][j][0]*2+dp[i-1][j][1]*2)%mod;
            dp[i][j][0]=(dp[i][j][0]+dp[i-1][j][0]+dp[i-1][j][1]*2)%mod;
            dp[i][j+1][0]=(dp[i][j+1][0]+dp[i-1][j][0]+dp[i-1][j][1])%mod;
            dp[i][j][1]=(dp[i][j][1]+dp[i-1][j][1])%mod;
        }
    }
    int t,n,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        printf("%d\n",(dp[n][k][0]+dp[n][k][1])%mod);
    }
    return 0;
}
