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
const int maxn=200+10;
const int maxm=20000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
bool vis[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(to,cap,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,-cost,head[to]);
    head[to]=nEdge;
}
int dfs(int u,int a,int t,int &cost)
{
    if(u==t)
    {
        cost+=a*d[t];
        return a;
    }
    vis[u]=true;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(e.cap&&d[e.to]==d[u]+e.cost&&!vis[e.to])
        {
            f=dfs(e.to,min(a,e.cap),t,cost);
            flow+=f;
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
bool changes(int n)
{
    int mind=inf;
    for(int i=0;i<=n;++i)
    {
        if(!vis[i]) continue;
        for(int k=head[i];k!=-1;k=edges[k].next)
            if(!vis[edges[k].to]&&edges[k].cap)
                mind=min(mind,d[i]+edges[k].cost-d[edges[k].to]);
    }
    if(mind==inf) return false;
    for(int i=0;i<=n;++i)
        if(!vis[i]) d[i]+=mind;
    return true;
}
struct Point
{
    int x,y,z,w;
    void read()
    {
        scanf("%d%d%d%d",&x,&y,&z,&w);
    }
    int operator * (const Point &a) const
    {
        return (int)sqrt((double)(x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)+(z-a.z)*(z-a.z));
    }
}pt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int sum=0;
        int S=0,T=n*2+1;
        for(int i=1;i<=n;++i)
          pt[i].read(),sum+=pt[i].w;
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,pt[i].w,0);
            AddEdges(i+n,T,pt[i].w,0);
            for(int j=i+1;j<=n;++j)
            {
                int len=pt[i]*pt[j];
                AddEdges(i,j+n,inf,len);
                AddEdges(j,i+n,inf,len);
            }
        }
        int flow=0,cost=0;
        memset(d,0x3f,sizeof(d));
        d[S]=0;
        while(true)
        {
            memset(vis,0,sizeof(vis));
            flow+=dfs(S,inf,T,cost);
            if(!changes(T)) break;
        }
        if(flow!=sum)
          printf("-1\n");
        else
          printf("%d\n",cost);
    }
    return 0;
}
