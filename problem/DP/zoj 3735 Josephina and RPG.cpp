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
const int maxn=10000+10;
const int maxm=120+10;
double dp[maxn][maxm];
double rate[maxm][maxm];
int a[maxn];
int C(int x,int y)
{
    int a=1,b=1;
    for(int i=0;i<x;++i)
       a*=(y-i);
    for(int i=x;i>=1;--i)
       b*=i;
    return a/b;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&m))
    {
        memset(dp,0,sizeof(dp));
        m=C(3,m);
        for(int i=0;i<m;++i)
          for(int j=0;j<m;++j)
            scanf("%lf",&rate[i][j]);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
          scanf("%d",&a[i]);
        double mx=0;
        for(int i=0;i<m;++i)
        {
            dp[1][i]=rate[i][a[1]];
            mx=max(rate[i][a[1]],mx);
        }
        dp[1][a[1]]=max(dp[1][a[1]],mx);
        for(int i=2;i<=n;++i)
        {
            mx=0;
            for(int j=0;j<m;++j)
            {
                dp[i][j]=dp[i-1][j]*rate[j][a[i]];
                mx=max(mx,dp[i][j]);
            }
            dp[i][a[i]]=max(mx,dp[i][a[i]]);
        }
        mx=0;
        for(int i=0;i<m;++i)
          mx=max(dp[n][i],mx);
        printf("%.6lf\n",mx);
    }
    return 0;
}
