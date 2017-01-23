struct Edge
{
    int to,cap,next;
    Edge(){};
    Edge(int tt,int cc,int nx)
    {to=tt;cap=cc;next=nx;};
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],cur[maxn],n,m,S,T;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
}
bool BFS()
{
    memset(d,0xff,sizeof(d));
    queue<int>q;
    q.push(S);
    d[S]=0;
    int v;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].to;
            if(d[v]==-1&&edges[k].cap>0)
            {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    return d[T]!=-1;
}
int DFS(int u,int a)
{
    if(u==T||a==0) return a;
    int flow=0,f,v;
    for(int &k =cur[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].to;
        if(d[v]==d[u]+1&&(f=DFS(v,min(a,edges[k].cap)))>0)
        {
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=n;++i) cur[i]=head[i];
        flow+=DFS(S,inf);
    }
    return flow;
}