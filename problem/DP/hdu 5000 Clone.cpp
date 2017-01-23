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
const int maxn = 2000 + 10;
const int mod = 1e9 + 7;
int a[maxn],dp[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,sum = 0;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&a[i]);
            sum += a[i];
        }
        sum /= 2;
        memset(dp,0,sizeof(dp));
        for(int i = 0;i <= a[1];++i)
            dp[1][i] = 1;
        for(int i = 2;i <= n;++i)
            for(int j = 0;j <= sum;++j)
                for(int k = 0;k <= j && k <= a[i];++k)
                {
                    dp[i][j] += dp[i-1][j-k];
                    if(dp[i][j] >= mod) dp[i][j] -= mod;
                }
        printf("%d\n",dp[n][sum]);
    }
    return 0;
}
