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
bool changes(int n)
{
    int mind=inf;
    for(int u=0;u<=n;++u)
    {
        if(!vis[u]) continue;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(!vis[e.to]&&e.cap)
                mind=min(mind,d[u]+e.cost-d[e.to]);
        }
    }
    if(mind==inf) return false;
    for(int i=0;i<=n;++i)
        if(!vis[i]) d[i]+=mind;
    return true;
}
int dfs(int u,int a,int t,int &cost)
{
    if(u==t||a==0)
    {
        cost+=d[t]*a;
        return a;
    }
    vis[u]=true;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(!vis[e.to]&&d[e.to]==d[u]+e.cost)
        {
            f=dfs(e.to,min(a,e.cap),t,cost);
            if(!f) continue;
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            flow+=f;a-=f;
            if(a==0) return flow;
        }
    }
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d",&n);
        int u,v,w,c;
        int S=0,T=n+1,sum=0;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,inf,0);
            AddEdges(S,v,w,0);
            AddEdges(u,T,w,0);
            sum+=w;
        }
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&w,&c);
            AddEdges(v,u,w,c);
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
        if(sum!=flow) cost=-1;
        printf("Case #%d: %d\n",++tcase,cost);
    }
    return 0;
}
