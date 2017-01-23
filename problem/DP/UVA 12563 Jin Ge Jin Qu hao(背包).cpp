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
const int maxn = 10000 + 10;
int dp[55][maxn],w[maxn];
bool flag[55][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,tcase = 0;
    scanf("%d",&T);
    while(T--)
    {
        int n,t;
        scanf("%d%d",&n,&t);
        for(int i = 1;i <= n;++i)
            scanf("%d",&w[i]);
        memset(dp,0,sizeof(dp));
        memset(flag,0,sizeof(flag));
        flag[0][0] = true;
        for(int i = 0;i < n;++i)
            for(int j = 0;j <= t;++j)
            {
                if(!flag[i][j]) continue;
                if(j + w[i+1] <= t)
                {
                    flag[i+1][j + w[i+1]] = true;
                    dp[i+1][j + w[i+1]] = max(dp[i][j] + 1,dp[i+1][j + w[i+1]]);
                }
                flag[i+1][j] = true;
                dp[i+1][j] = max(dp[i+1][j],dp[i][j]);
            }
        int maxv = 0,maxtime = 0;
        for(int i = t - 1;i >= 0;--i)
        {
            if(dp[n][i] > maxv)
            {
                maxv = dp[n][i];
                maxtime = i;
            }
        }
        if(t) maxv ++,maxtime += 678;
        printf("Case %d: %d %d\n",++tcase,maxv,maxtime);
    }
    return 0;
}
