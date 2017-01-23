#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
const int mod=1000000007;
ll dp[2][maxn][maxn],p[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    p[0]=1;
    for(int i=1;i<=n;++i)
        p[i]=(p[i-1]<<1)%mod;
    memset(dp,0,sizeof(dp));
    dp[0][0][0]=1;
    for(int i=1;i<=n;++i)
    {
        int now=i&1;
        memset(dp[now],0,sizeof(dp[now]));
        for(int j=0;j<i&&j<=k;++j)
            for(int last=0;last<i;++last)
            {
                if(!dp[now^1][j][last]) continue;
                dp[now][j][last]+=dp[now^1][j][last];
                dp[now][j][last]+=dp[now^1][j][last]*(p[last]-1)%mod;
                if(dp[now][j][last]>=mod) dp[now][j][last]-=mod;
                dp[now][j+1][i]+=dp[now^1][j][last]*(p[i]-p[last]+mod)%mod;
                if(dp[now][j+1][i]>=mod) dp[now][j+1][i]-=mod;
            }
    }
    ll ans=0;
    for(int i=0;i<=n;++i)
    {
        ans+=dp[n&1][k][i];
        if(ans>=mod) ans-=mod;
    }
    printf("%I64d\n",ans);
    return 0;
}
