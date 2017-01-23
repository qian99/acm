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
int dp[30][2];
int getpoints(int x,int y)
{
    if(x==0) return 2;
    if(x==y) return 1;
    if(abs(x-y)==2) return 4;
    return 3;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k;
    while(~scanf("%d",&k))
    {
        if(k==0) break;
        for(int i=0;i<25;++i) dp[i][0]=inf;
        dp[k][0]=2;
        int t=1,x,y,tmp;
        while(scanf("%d",&k))
        {
            if(k==0) break;
            for(int i=0;i<25;++i) dp[i][t]=inf;
            for(int i=0;i<5;++i)
             for(int j=i+1;j<5;++j)
             {
                 if(dp[i*5+j][t^1]==inf) continue;
                 if(k==i||k==j) dp[i*5+j][t]=min(dp[i*5+j][t],dp[i*5+j][t^1]+1);
                 //i->k
                 tmp=getpoints(i,k);
                 x=k;y=j;
                 if(x>y) swap(x,y);
                 dp[x*5+y][t]=min(dp[x*5+y][t],dp[i*5+j][t^1]+tmp);
                 //j->k
                 tmp=getpoints(j,k);
                 x=i;y=k;
                 if(x>y) swap(x,y);
                 dp[x*5+y][t]=min(dp[x*5+y][t],dp[i*5+j][t^1]+tmp);
             }
            t^=1;
        }
        int ans=inf;
        for(int i=0;i<25;++i) ans=min(ans,dp[i][t^1]);
        printf("%d\n",ans);
    }
    return 0;
}
