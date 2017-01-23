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
const int mod = 1e9;
const int maxn = 55;
int dp[maxn][1<<15],c[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n;++i)
            scanf("%d",&c[i]);
        for(int i = 0;i < (1<<m);++i)
            dp[0][i] = 1;
        for(int i = 0;i < (1<<m); i += c[0])
            dp[0][i] = 0;
        for(int i = 0;i < n - 1;++i)
        {
            for(int j = 0;j < (1<<m);++j)
                dp[i+1][j^((1<<m)-1)] = dp[i][j];
            for(int j = 0;j < m;++j)
                for(int k = 0;k < (1<<m);++k)
                {
                    if(k & (1<<j))
                    {
                        dp[i+1][k^(1<<j)] += dp[i+1][k];
                        if(dp[i+1][k^(1<<j)] >= mod) dp[i+1][k^(1<<j)] -= mod;
                    }
                }
            for(int j = 0;j < (1<<m); j += c[i+1])
                dp[i+1][j] = 0;
        }
        int ans = 0;
        for(int i = 0;i < (1<<m);++i)
        {
            ans += dp[n-1][i];
            if(ans >= mod) ans -= mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}
