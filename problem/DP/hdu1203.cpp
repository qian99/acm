#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=10000+10;
double dp[maxn],p[maxn];
int cost[maxn];
int main()
{
    int m,n;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int co;
        double po;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%lf",&co,&po);
            cost[i]=co;
            p[i]=1-po;
        }
        for(int i=0;i<=n;++i)
          dp[i]=1.0;
        for(int i=1;i<=m;++i)
        {
            for(int j=n;j>=cost[i];--j)
            {
                dp[j]=min(dp[j],dp[j-cost[i]]*p[i]);
            }
        }
        printf("%.1lf%%\n",(1.0-dp[n])*100);
    }
    return 0;
}
