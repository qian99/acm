#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int N=10000+10;
const int mod=3000+10;
const int M=100+10;
int val[N],dp[mod][M];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&val[i]);
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=m;++i)
        for(int j=1;j<i;++j)
            dp[i%mod][i-j]=val[i]+val[j];
    for(int i=m+1;i<=n;++i)
    {
        for(int j=i-1;j>i-m;--j)
        {
            if(j<=0) continue;
            dp[i%mod][i-j]=inf;
            for(int k=j-1;k>=i-m&&k>=1;--k)
            {
                if(dp[j%mod][j-k]+val[i]<dp[i%mod][i-j])
                    dp[i%mod][i-j]=dp[j%mod][j-k]+val[i];
            }
        }
    }
    int ans=inf;
    for(int i=n;i>n-m;--i)
    {
        for(int j=i-1;j>i-m&&j>=1;--j)
        {
            if(j+m-1>=n&&dp[i%mod][i-j]<ans)
                ans=dp[i%mod][i-j];
        }
    }
    printf("%d\n",ans);
    return 0;
}

