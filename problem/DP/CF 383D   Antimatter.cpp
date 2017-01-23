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
const int maxn=1000+10;
const int maxm=20000+10;
const int mod=1000000007;
int dp[maxn][maxm],a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    memset(dp,0,sizeof(dp));
    dp[0][10000]=1;
    for(int i=1;i<=n;++i)
    {
        if(a[i]<0) a[i]=-a[i];
        for(int j=a[i];j<maxm-a[i];++j)
        {
            if(dp[i-1][j-a[i]])
                dp[i][j]=(dp[i][j]+dp[i-1][j-a[i]])%mod;
            if(dp[i-1][j+a[i]])
                dp[i][j]=(dp[i][j]+dp[i-1][j+a[i]])%mod;
        }
        dp[i][10000]++;
    }
    int ans=(-n+mod)%mod;
    for(int i=1;i<=n;++i)
        ans=(ans+dp[i][10000])%mod;
    printf("%d\n",ans);
    return 0;
}
