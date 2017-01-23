#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
int dp[2010][1010];
int w[2010];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&w[i]);
        sort(w+1,w+n+1);
        memset(dp,0,sizeof(dp));
        for(int i=2;i<=n;++i)
        {
            int l=i/2;
            for(int j=1;j<=l;++j)
            {
                if(i==2*j)
                {
                    dp[i][j]=dp[i-2][j-1]+(w[i]-w[i-1])*(w[i]-w[i-1]);
                }
                else
                {
                    dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+(w[i]-w[i-1])*(w[i]-w[i-1]));
                }
            }
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}
