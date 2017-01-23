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
const int maxn=1100000+10;
const int mod=1000000007;
ll dp[maxn][7];
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n=strlen(str);
    memset(dp,0,sizeof(dp));
    if(str[0]=='?')
        dp[0][0]=dp[0][2]=dp[0][4]=1;
    else if(str[0]=='1') dp[0][2]=1;
    else if(str[0]=='*') dp[0][4]=1;
    else if(str[0]=='0') dp[0][0]=1;
    for(int i=1;i<n;++i)
    {
        if(str[i]=='?')
        {
            dp[i][0]=(dp[i-1][0]+dp[i-1][1])%mod;
            dp[i][1]=(dp[i-1][4])%mod;
            dp[i][2]=(dp[i-1][0]+dp[i-1][1])%mod;
            dp[i][3]=(dp[i-1][4])%mod;
            dp[i][4]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][4])%mod;
        }
        else if(str[i]=='*')
        {
            dp[i][4]=(dp[i-1][2]+dp[i-1][3]+dp[i-1][4])%mod;
        }
        else if(str[i]=='0')
        {
            dp[i][0]=(dp[i-1][0]+dp[i-1][1])%mod;
        }
        else if(str[i]=='1')
        {
            dp[i][1]=(dp[i-1][4])%mod;
            dp[i][2]=(dp[i-1][0]+dp[i-1][1])%mod;
        }
        else
            dp[i][3]=(dp[i-1][4])%mod;
    }
    ll ans=dp[n-1][0]+dp[n-1][1]+dp[n-1][4];
    ans%=mod;
    cout<<ans<<endl;
    return 0;
}