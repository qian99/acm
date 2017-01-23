#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
int dp[maxn][maxn],w[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=0;i<n;++i)
        scanf("%d",&w[i]);
    for(int k=3;k<=n;++k)
        for(int i=0;i<=n-k;++i)
        {
            dp[i][i+k-1]=dp[i][i+1]+dp[i+1][i+k-1]+w[i]*w[i+1]*w[i+k-1];
            for(int j=i+2;j<i+k-1;++j)
                dp[i][i+k-1]=min(dp[i][i+k-1],dp[i][j]+dp[j][i+k-1]+w[i]*w[j]*w[i+k-1]);
        }
    printf("%d\n",dp[0][n-1]);
    return 0;
}
