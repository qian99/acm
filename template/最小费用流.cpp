struct Edge
{
    int from,to,cap,flow,cost,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int co,int nx)
    {from=ff;to=tt;cap=cc;flow=fl;cost=co;next=nx;}
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],p[maxn],a[maxn];
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(from,to,cap,0,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,int &cost)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    d[s]=0;a[s]=inf;p[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                a[e.to]=min(a[u],e.cap-e.flow);
                if(!inq[e.to]){inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    flow+=a[t];
    cost+=a[t]*d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].flow+=a[t];
        edges[p[u]^1].flow-=a[t];
        u=edges[p[u]].from;
    }
    return true;
}
void mincost(int s,int t,int &flow,int &cost)
{
    flow=0,cost=0;
    while(spfa(s,t,flow,cost));
}