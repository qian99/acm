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
const int maxm = 35;
const int maxn = 100 + 10;
int dp[maxm][maxn],P[maxm],n,m;
int check(int limit)
{
    if(limit == 0) return 0;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1;i <= m;++i)
    {
        int K = P[i]/limit;
        for(int j = 0;j <= n;++j)
        {
            dp[i][j] = dp[i-1][j];
            if(j >= K)
                dp[i][j] = min(dp[i][j],dp[i-1][j-K] + P[i]);
        }
        if(K > n)
            dp[i][n] = min(dp[i][n],dp[i-1][0] + P[i]);
    }
    if(dp[m][n] == inf) return -1;
    return dp[m][n];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        int L = 0, R = 0;
        for(int i = 1;i <= m;++i)
        {
            scanf("%d",&P[i]);
            R = max(R,P[i]);
        }
        R++;
        while(R - L > 1)
        {
            int mid = (L+R)>>1;
            if(check(mid) != -1)
                L = mid;
            else
                R = mid;
        }
        printf("%d %d\n",L,check(L));
    }
    return 0;
}
