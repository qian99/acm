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
const double INF=1e18;
struct Edge
{
    int u,v,next;
};
struct Points
{
    int x,y;
};
Points points[maxn];
Edge edges[maxn<<1];
int head[maxn],pa[maxn],nEdge;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].u=u;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
double ways[maxn][maxn],dp[maxn][maxn],d[maxn];
bool vis[maxn];
void Init(int n)
{
    for(int i=0;i<n;++i)
    {
        ways[i][i]=0;
        for(int j=0;j<n;++j)
          dp[i][j]=INF;
    }
    memset(head,0xff,sizeof(head));
    nEdge=-1;
}
double Len(Points a,Points b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
double prime(int n)
{
    for(int i=0;i<n;++i) d[i]=ways[0][i];
    memset(vis,0,sizeof(vis));
    memset(pa,0,sizeof(pa));
    vis[0]=true;pa[0]=-1;d[0]=0;
    double minlen,res=0;
    int pos;
    for(int i=1;i<n;++i)
    {
        minlen=INF;
        for(int j=0;j<n;++j)
        {
            if(!vis[j]&&d[j]<minlen)
            {
                minlen=d[j];
                pos=j;
            }
        }
        res+=minlen;
        vis[pos]=true;
        if(pa[pos]!=-1)
        {
            AddEdge(pos,pa[pos]);
            AddEdge(pa[pos],pos);
        }
        for(int k=0;k<n;++k)
        {
            if(!vis[k]&&d[k]>ways[pos][k])
            {
                d[k]=ways[pos][k];
                pa[k]=pos;
            }
        }
    }
    return res;
}
double dfs(int u,int fa,int p)
{
    double res=INF;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        double tmp=dfs(v,u,p);
        res=min(tmp,res);
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    if(fa!=p)
      res=min(res,ways[u][p]);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        Init(n);
        for(int i=0;i<n;++i)
           scanf("%d%d",&points[i].x,&points[i].y);
        for(int i=0;i<n;++i)
          for(int j=i+1;j<n;++j)
             ways[i][j]=ways[j][i]=Len(points[i],points[j]);
        double tmp=prime(n);
        double ans=tmp;
        for(int i=0;i<n;++i)
          dfs(i,-1,i);
        int u,v;
        for(int i=0;i<=nEdge;i+=2)
        {
            u=edges[i].u;v=edges[i].v;
            if(u!=0&&v!=0)
            ans=max(ans,tmp-ways[u][v]+dp[u][v]);
        }
        printf("%.2lf\n",ans*k);
    }
    return 0;
}
