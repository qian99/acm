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
const int maxn=100+10;
int dp[maxn][maxn],a[maxn][maxn];
int ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int F,V;
    while(cin>>F>>V)
    {
        for(int i=1;i<=F;++i)
          for(int j=1;j<=V;++j)
            scanf("%d",&a[i][j]);
        for(int i=0;i<=V;++i)
          for(int j=0;j<=F;++j)
            dp[i][j]=-inf;
        dp[0][0]=0;
        for(int i=1;i<=V;i++)
        {
            int mx=min(i,F);
            dp[i][0]=dp[i-1][0];
            for(int j=1;j<=mx;++j)
              dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+a[j][i]);
        }
        int k=dp[V][F];
        for(int i=F;i>=1;i--)
        {
            for(int j=i;j<=V;++j)
            {
                if(dp[j-1][i-1]+a[i][j]==k)
                {
                    k-=a[i][j];
                    ans[i]=j;
                    break;
                }
            }
        }
        cout<<dp[V][F]<<endl;
        cout<<ans[1];
        for(int i=2;i<=F;++i)
          cout<<" "<<ans[i];
        cout<<endl;
    }
    return 0;
}
