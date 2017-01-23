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
int flow=0,cost=0;
memset(d,0x3f,sizeof(d));
d[S]=0;
while(true)
{
   memset(vis,0,sizeof(vis));
   flow+=dfs(S,inf,T,cost);
   if(!changes(T)) break;
}