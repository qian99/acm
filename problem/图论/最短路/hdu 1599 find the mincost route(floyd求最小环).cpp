#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#define inf 100000000
using namespace std;
const int maxn=100+10;
int ways[maxn][maxn],dp[maxn][maxn],n,m;
int main()
{
    //freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&m))
    {
        int i,j,k,u,v,w;
        for(i=1;i<=n;++i)
          for(j=1;j<=n;++j)
             if(i==j) dp[i][j]=ways[i][j]=0;
             else dp[i][j]=ways[i][j]=inf;
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            if(w<ways[u][v])
                dp[u][v]=dp[v][u]=ways[u][v]=ways[v][u]=w;
        }
        int ans=inf;
        for(k=1;k<=n;++k)
        {
            for(i=1;i<k;++i)
             for(j=i+1;j<k;++j)
               ans=min(ans,dp[i][j]+ways[i][k]+ways[k][j]);
            for(i=1;i<=n;++i)
             for(j=1;j<=n;++j)
               dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
        }
        if(ans==inf)
            printf("It's impossible.\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}
