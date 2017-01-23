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
int dis[1<<17][20],dp[3][1<<17];
bool inq[1<<17][20];
int d[20][20];
struct State
{
    int state,pos;
};
void bfs(int n)
{
    memset(inq,0,sizeof(inq));
    int N=1<<n;
    memset(dis,127,sizeof dis);
    queue<State>q;
    q.push((State){0,0});
    dis[0][0]=0;
    inq[0][0]=true;
    while(!q.empty())
    {
        State x=q.front();q.pop();
        inq[x.state][x.pos]=false;
        for(int i=0;i<n;++i)
        {
            int p=1<<i;
            if(dis[x.state|p][i]>dis[x.state][x.pos]+d[x.pos][i])
            {
                dis[x.state|p][i]=dis[x.state][x.pos]+d[x.pos][i];
                if(!inq[x.state|p][i])
                {
                    inq[x.state|p][i]=true;
                    q.push((State){x.state|p,i});
                }
            }
        }
    }
    for(int i=0;i<N;++i)
    {
        dp[0][i]=inf;
        for(int j=0;j<n;++j)
          dp[0][i>>1]=min(dp[0][i>>1],dis[i][j]);
    }
    dp[0][0]=0;
}
int DP(int n,int limit)
{
    int N=1<<n;
    for(int i=0;i<N;++i)
    {
        dp[1][i]=inf;
        for(int j=i;;j=(j-1)&i)
        {
            if(dp[0][j]!=inf&&dp[0][i^j]!=inf)
               dp[1][i]=min(dp[1][i],max(dp[0][j],dp[0][i^j]));
            if(j==0) break;
        }
    }
    int ans=inf;
    for(int i=0;i<N;++i)
    {
        for(int j=i;;j=(j-1)&i)
        {
            if((i&limit)==limit)
            {
                if(dp[0][i^j]!=inf&&dp[1][j]!=inf)
                   ans=min(ans,max(dp[0][i^j],dp[1][j]));
            }
            if(j==0) break;
        }
    }
    if(ans==inf) return -1;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n,m,k;
        scanf("%d%d",&n,&m);
        memset(d,127,sizeof(d));
        int x,y,z;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            x--;y--;
            d[x][y]=min(d[x][y],z);
            d[y][x]=d[x][y];
        }
        scanf("%d",&k);
        int limit=0;
        for(int i=0;i<k;++i)
        {
            scanf("%d",&x);
            x-=2;
            x=(1<<x);
            limit|=x;
        }
        bfs(n);
        int ans=DP(n-1,limit);
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}
