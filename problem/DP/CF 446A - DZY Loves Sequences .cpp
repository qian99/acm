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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000+10;
int a[maxn],dp[maxn][3][2];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    memset(dp,0xff,sizeof(dp));
    dp[1][0][1] = 1;
    dp[1][1][0] = 1;
    int ans = 1;
    for(int i = 2;i <= n;++i)
    {
        if(dp[i-1][0][1] != -1)
            dp[i][1][1] = dp[i-1][0][1] + 1;
        if(dp[i-1][1][0] != -1)
        {
            if(a[i] > a[i-1])
                dp[i][1][0] = dp[i-1][1][0] + 1;
            dp[i][2][1] = dp[i-1][1][0] + 1;
        }
        if(dp[i-1][1][1] != -1)
        {
            if(a[i] > a[i-1])
                dp[i][1][1] =  max(dp[i][1][1],dp[i-1][1][1] + 1);
        }
        if(dp[i-1][2][1] != -1)
            if(a[i] > a[i-2] +1)
                dp[i][1][1] = max(dp[i][1][1],dp[i-1][2][1] + 1);
        dp[i][0][1] = max(dp[i][0][1],1);
        dp[i][1][0] = max(dp[i][1][0],1);
        for(int j = 0; j < 3; ++j)
        {
            ans = max(ans, dp[i][j][0]);
            ans = max(ans, dp[i][j][1]);
        }
    }
    printf("%d\n",ans);
    return 0;
}