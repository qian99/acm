struct Edge
{
    int from,to,dist;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode & a) const
    {
        return a.d<d;
    }
};
struct Dijkstra
{
    int n,m;
    vector<Edge>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int dis[maxn],p[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int dist)
    {
        edges.push_back((Edge){from,to,dist});
        m=edges.size();
        G[from].push_back(m-1);
    }
    void dijkstra(int s)
    {
        priority_queue<HeapNode>q;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;++i) dis[i]=inf;
        dis[s]=0;
        HeapNode hp=(HeapNode){0,s};
        q.push(hp);
        while(!q.empty())
        {
           hp=q.top();q.pop();
           int u=hp.u;
           if(vis[u]) continue;
           vis[u]=true;
           for(int i=0;i<G[u].size();++i)
           {
               Edge e=edges[G[u][i]];
               if(dis[e.to]>dis[u]+e.dist)
               {
                   dis[e.to]=dis[u]+e.dist;
                   p[e.to]=G[u][i];
                   q.push((HeapNode){dis[e.to],e.to});
               }
           }
        }
    }
};