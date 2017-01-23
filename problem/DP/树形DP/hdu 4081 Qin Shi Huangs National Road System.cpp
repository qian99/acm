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
const int maxn=1000+10;
const double INF=1e10;
struct Edge
{
    int u,v,next;
};
struct Point
{
    int x,y;
}points[maxn];
Edge edges[maxn<<1];
int head[maxn],nEdge;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].u=u;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
double Len(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
int n,val[maxn],pa[maxn],dp[maxn][maxn];
double ways[maxn][maxn],d[maxn],ans,prval;
bool vis[maxn];
void prime()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i) d[i]=ways[1][i],pa[i]=1;
    vis[1]=true;pa[1]=-1;prval=0;
    double minval;
    int pos;
    for(int i=1;i<n;++i)
    {
        minval=INF;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j]&&d[j]<minval)
            {
                minval=d[j];
                pos=j;
            }
        }
        prval+=minval;
        vis[pos]=true;
        if(pa[pos]!=-1)
        {
            AddEdge(pos,pa[pos]);
            AddEdge(pa[pos],pos);
        }
        for(int k=1;k<=n;++k)
        {
            if(!vis[k]&&d[k]>ways[pos][k])
            {
                d[k]=ways[pos][k];
                pa[k]=pos;
            }
        }
    }
}
int dfs(int u,int fa,int p)
{
    int res=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        int tmp=dfs(v,u,p);
        res=max(res,tmp);
        dp[u][v]=dp[v][u]=max(dp[u][v],tmp);
    }
    if(u!=p)
      res=max(res,val[u]+val[p]);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
           scanf("%d%d%d",&points[i].x,&points[i].y,&val[i]);
        for(int i=1;i<=n;++i)
          for(int j=i;j<=n;++j)
             ways[i][j]=ways[j][i]=Len(points[i],points[j]);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        prime();
        ans=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
          dfs(i,-1,i);
        int u,v;
        for(int i=0;i<=nEdge;i+=2)
        {
            u=edges[i].u;v=edges[i].v;
            ans=max(ans,(dp[u][v])/(prval-ways[u][v]));
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
