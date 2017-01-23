struct Edge
{
    int from,to,cap,flow;
};
struct ISAP
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int d[maxn],cur[maxn];
    int p[maxn],num[maxn];
    void clear(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int cap)
    {
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    void BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int>q;
        d[t]=0;vis[t]=1;
        q.push(t);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge e=edges[G[x][i]];
                if(!vis[e.from]&&e.cap>e.flow)
                {
                    vis[e.from]=true;
                    d[e.from]=d[x]+1;
                    q.push(e.from);
                }
            }
        }
    }
    int Augment()
    {
        int x=t,a=inf;
        while(x!=s)
        {
            Edge e=edges[p[x]];
            a=min(a,e.cap-e.flow);
            x=e.from;
        }
        x=t;
        while(x!=s)
        {
            edges[p[x]].flow+=a;
            edges[p[x]^1].flow-=a;
            x=edges[p[x]].from;
        }
        return a;
    }
    int Maxflow(int s,int t)
    {
        this->s=s;this->t=t;
        int flow=0;
        BFS();
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;++i) num[d[i]]++;
        int x=s;
        memset(cur,0,sizeof(cur));
        while(d[s]<n)
        {
            if(x==t)
            {
                flow+=Augment();
                x=s;
            }
            int ok=0;
            for(int i=cur[x];i<G[x].size();++i)
            {
                Edge e=edges[G[x][i]];
                if(e.cap>e.flow&&d[x]==d[e.to]+1)
                {
                    ok=1;
                    cur[x]=i;
                    p[e.to]=G[x][i];
                    x=e.to;
                    break;
                }
            }
            if(!ok)
            {
                int mm=n-1;
                for(int i=0;i<G[x].size();++i)
                {
                    Edge e=edges[G[x][i]];
                    if(e.cap>e.flow) mm=min(mm,d[e.to]);
                }
                if(--num[d[x]]==0) break;
                num[d[x]=mm+1]++;
                cur[x]=0;
                if(x!=s) x=edges[p[x]].from;
            }
        }
        return flow;
    }
}isap;