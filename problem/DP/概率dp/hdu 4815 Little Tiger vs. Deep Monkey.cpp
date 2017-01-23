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
const int maxn = 40000+10;
double dp[55][maxn];
int val[55];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        double P;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        scanf("%lf",&P);
        for(int i = 1;i <= n;++i)
            scanf("%d",&val[i]);
        int sum = 0;
        for(int i = 1;i <= n;++i) sum += val[i];
        dp[0][0] = 1.0;
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j <= sum;++j)
                if(dp[i][j])
                {
                    dp[i+1][j+val[i+1]] += dp[i][j]*0.5;
                    dp[i+1][j] += dp[i][j]*0.5;
                }
        }
        int ans = 0;
        double tot = 0;
        for(int i = 0;i <= sum;++i)
        {
            tot += dp[n][i];
            if(tot >= P)
            {
                ans = i;
                break;
            }
        }
        if(P == 0) ans = 0;
        printf("%d\n",ans);
    }
    return 0;
}
