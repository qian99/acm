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
const int maxn=1000+2;
const int mod=1000000007;
int dp[maxn][maxn];
char str[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        dp[0][0]=1;
        int k;
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
            {
                if(!dp[i][j]) continue;
                k=i+j+1;
                if((i&1)&&(j&1))
                {
                    if(str[k]=='B')
                    {
                        dp[i][j+1]+=dp[i][j];
                        dp[i+1][j]+=dp[i][j];
                        if(dp[i][j+1]>=mod) dp[i][j+1]-=mod;
                        if(dp[i+1][j]>=mod) dp[i+1][j]-=mod;
                    }
                }
                else if(i&1)
                {
                    if(str[k]=='W')
                    {
                        dp[i][j+1]+=dp[i][j];
                        if(dp[i][j+1]>=mod) dp[i][j+1]-=mod;
                    }
                    else
                    {
                        dp[i+1][j]+=dp[i][j];
                        if(dp[i+1][j]>=mod) dp[i+1][j]-=mod;
                    }
                }
                else if(j&1)
                {
                    if(str[k]=='W')
                    {
                        dp[i+1][j]+=dp[i][j];
                        if(dp[i+1][j]>=mod) dp[i+1][j]-=mod;
                    }
                    else
                    {
                        dp[i][j+1]+=dp[i][j];
                        if(dp[i][j+1]>=mod) dp[i][j+1]-=mod;
                    }

                }
                else
                {
                    if(str[k]=='W')
                    {
                        dp[i][j+1]+=dp[i][j];
                        dp[i+1][j]+=dp[i][j];
                        if(dp[i][j+1]>=mod) dp[i][j+1]-=mod;
                        if(dp[i+1][j]>=mod) dp[i+1][j]-=mod;
                    }

                }
            }
        int ans=dp[n][n];
        printf("%d\n",ans);
    }
    return 0;
}