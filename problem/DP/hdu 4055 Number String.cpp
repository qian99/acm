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
const int maxn=1000+10;
const int mod=1000000007;
char str[maxn];
int dp[maxn][maxn],sum[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%s",str))
    {
        n=strlen(str);
        n++;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i) sum[i][0]=0;
        for(int i=1;i<=n;++i)
        {
            dp[1][i]=1;
            sum[1][i]=i;
        }
        for(int i=2;i<=n;++i)
        {
            for(int j=1;j<=n-i+1;++j)
            {
                if(str[i-2]=='I'||str[i-2]=='?')
                  dp[i][j]+=sum[i-1][j]-sum[i-1][0];
                if(str[i-2]=='D'||str[i-2]=='?')
                  dp[i][j]+=sum[i-1][n-i+2]-sum[i-1][j];
                dp[i][j]%=mod;
                sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
            }
        }
        int res=(dp[n][1]+mod)%mod;
        printf("%d\n",res);
    }
    return 0;
}
