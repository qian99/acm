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
const int maxn = 5000 + 5;
int a[maxn];
ll sum[maxn],dp[maxn][maxn],maxv[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    sum[0] = 0;
    for(int i = 1;i <= n;++i)
        sum[i] = sum[i-1] + a[i];
    memset(dp,0xff,sizeof(dp));
    memset(maxv,0,sizeof(maxv));
    dp[0][0] = 0;
//    maxv[0][0] = 0;
    for(int j = 1;j <= k;++j)
    {
        for(int i = 1;i <= n;++i)
        {
            if(i - m >= 0)
            {
                dp[i][j] = max(dp[i][j],maxv[i-m] + sum[i] - sum[i-m]);
            }
        }
        for(int i = 1;i <= n;++i)
            maxv[i] = max(maxv[i-1],dp[i][j]);
    }
    ll ans = 0;
    for(int i = 1;i <= n;++i)
        if(dp[i][k] != -1)
            ans = max(ans,dp[i][k]);
    printf("%I64d\n",ans);
    return 0;
}