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
const int maxn=2000+10;
double val[maxn<<1],dp[maxn<<1][maxn];
double min(double a,double b)
{
    return fabs(a)<fabs(b)?a:b;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        double tmp,tmp2;
        for(int i=1;i<=n*2;++i)
            cin>>val[i];
        for(int i=0;i<=n*2;++i)
          for(int j=0;j<=n;++j) dp[i][j]=1e10;
        dp[0][0]=0;dp[0][1]=0;
        for(int i=1;i<=n*2;++i)
        {
            tmp=val[i]-floor(val[i]);
            tmp2=ceil(val[i])-val[i];
            if(i<=n) dp[i][i]=min(dp[i][i],dp[i-1][i-1]+tmp);
            for(int j=0;j<=n&&j<i;++j)
            {
                if(j==0) dp[i][j]=min(dp[i][j],dp[i-1][j]-tmp2);
                else dp[i][j]=min(dp[i-1][j-1]+tmp,dp[i-1][j]-tmp2);
            }
        }
        double ans=fabs(dp[n*2][n]);
        printf("%.3lf\n",ans);
    }
    return 0;
}
