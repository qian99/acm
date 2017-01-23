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
const int maxn=100+10;
int dp[maxn][maxn],sum[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        sum[0]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&sum[i]);
            sum[i]+=sum[i-1];
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;++i)
            dp[i][i]=0;
        for(int k=2;k<=n;++k)
        {
            for(int i=1;i<=n-k+1;++i)
            {
                dp[i][i+k-1]=dp[i+1][i+k-1]+(sum[i+k-1]-sum[i]);
                for(int j=i+1;j<i+k-1;++j)
                {
                    int tmp=(sum[i+k-1]-sum[j])*(j-i+1)+(sum[i]-sum[i-1])*(j-i);
                    dp[i][i+k-1]=min(dp[i][i+k-1],dp[i+1][j]+dp[j+1][i+k-1]+tmp);
                }
                dp[i][i+k-1]=min(dp[i][i+k-1],dp[i+1][i+k-1]+(sum[i]-sum[i-1])*(k-1));
            }
        }
        printf("Case #%d: %d\n",tcase,dp[1][n]);
    }
    return 0;
}
