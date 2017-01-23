#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<queue>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
char str[110];
int dp[110][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>str;
        int n=strlen(str);
        dp[0][0]=0;
        dp[0][1]=1;
        for(int i=1;i<=n;++i)
        {
            if(str[i-1]>='A'&&str[i-1]<='Z')
            {
                dp[i][0]=min(dp[i-1][0]+2,dp[i-1][1]+2);
                dp[i][1]=min(dp[i-1][0]+2,dp[i-1][1]+1);
            }
            else
            {
                dp[i][1]=min(dp[i-1][0]+2,dp[i-1][1]+2);
                dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]+2);
            }
        }
        cout<<min(dp[n][0],dp[n][1]+1)<<endl;
    }
    return 0;
}
