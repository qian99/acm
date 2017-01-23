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
const int maxn=50000+100;
struct Edge
{
    int v,dist;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int dp[maxn][2],dir[maxn];
void AddEdges(int u,int v,int dist)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].dist=dist;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0]=dp[u][1]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v!=fa)
        {
            dfs(v,u);
            int tmp=dp[v][0]+edges[k].dist;
            if(tmp>dp[u][0])
            {
                dp[u][1]=dp[u][0];
                dp[u][0]=tmp;
                dir[u]=v;
            }
            else if(tmp>dp[u][1]) dp[u][1]=tmp;
        }
    }
}
void dfs2(int u,int fa,int step)
{
    dp[u][0]=max(dp[u][0],step);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v!=fa)
        {
            if(dir[u]==v) dfs2(v,u,max(dp[u][1],step)+edges[k].dist);
            else dfs2(v,u,dp[u][0]+edges[k].dist);
        }
    }
}
int mind[maxn][19],maxd[maxn][19];
int p[31];
int lg(int x)
{
    int k=0;
    while(p[k+1]<=x) k++;
    return k;
}
void RMQ_init(int n)
{
    for(int i=1;i<=n;++i) maxd[i][0]=mind[i][0]=dp[i][0];
    for(int j=1;(p[j])<=n;++j)
      for(int i=1;i+p[j]-1<=n;++i)
      {
          mind[i][j]=min(mind[i][j-1],mind[i+p[j-1]][j-1]);
          maxd[i][j]=max(maxd[i][j-1],maxd[i+p[j-1]][j-1]);
      }
}
inline int max_RMQ(int L,int R,int x)
{
    return max(maxd[L][x],maxd[R-p[x]+1][x]);
}
inline int min_RMQ(int L,int R,int x)
{
    return min(mind[L][x],mind[R-p[x]+1][x]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=0;i<=30;++i) p[i]=1<<i;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(head,0xff,sizeof(head));
        memset(dir,0xff,sizeof(dir));
        nEdge=-1;
        int a,b,c;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b,c);
            AddEdges(b,a,c);
        }
        dfs(1,-1);
        dfs2(1,-1,0);
        RMQ_init(n);
        int l,r,mid,ans,x;
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&mid);
            l=r=1;ans=1;
            while(r<=n)
            {
                x=lg(r-l+1);
                int tmp=max_RMQ(l,r,x)-min_RMQ(l,r,x);
                if(tmp<=mid)
                {
                    ans=max(ans,r-l+1);
                    r++;
                }
                else l++;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
