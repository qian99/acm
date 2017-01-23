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
const int maxm=100000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
int val[maxn];
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
    for(int i=0;i<=n;++i) if(!vis[i]) d[i]+=mind;
    return true;
}
int dfs(int u,int a,int t,int &cost)
{
    if(u==t)
    {
        cost+=d[t]*a;
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
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=n+2;
        int a,b,c;
        val[0]=0;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b+1,inf,c);
        }
        for(int i=1;i<=n+1;++i)
        {
            c=val[i]-val[i-1];
            if(c>=0) AddEdges(S,i,c,0);
            else AddEdges(i,T,-c,0);
            if(i>1) AddEdges(i,i-1,inf,0);
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
        printf("%d\n",cost);
    }
    return 0;
}
