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
char str[maxn];
int dp[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%s",str))
    {
        if(str[0]=='e') break;
        n=strlen(str);
        memset(dp,0,sizeof(dp));
        int ans=0;
        for(int k=2;k<=n;++k)
            for(int i=0;i<=n-k;++i)
            {
                if(str[i]=='['&&str[i+k-1]==']')
                {
                    if(i+1>i+k-2)
                        dp[i][i+k-1]=2;
                    else
                        dp[i][i+k-1]=max(dp[i][i+k-1],dp[i+1][i+k-2]+2);
                }
                if(str[i]=='('&&str[i+k-1]==')')
                {
                    if(i+1>i+k-2)
                        dp[i][i+k-1]=2;
                    else
                        dp[i][i+k-1]=max(dp[i][i+k-1],dp[i+1][i+k-2]+2);
                }
                for(int j=i;j<=i+k-2;++j)
                    dp[i][i+k-1]=max(dp[i][i+k-1],dp[i][j]+dp[j+1][i+k-1]);
                ans=max(ans,dp[i][i+k-1]);
            }
        printf("%d\n",ans);
    }
    return 0;
}
