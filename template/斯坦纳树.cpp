struct Edge
{
    int v,w,next;
};
struct Node
{
    int u,state;
};
Edge edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn][1<<11],s[1<<11];
bool inq[maxn][1<<11];
queue<Node>q;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(inq,0,sizeof(inq));
    memset(s,0,sizeof(s));
    nEdge=-1;
    N=1<<(2*k);
    for(int i=1;i<=n;++i)
      for(int j=0;j<N;++j)
        d[i][j]=inf;
    int u,v,w;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }
    for(int i=1;i<=k;++i)
    {
        s[i]=1<<(i-1);d[i][s[i]]=0;
        s[n-k+i]=1<<(k+i-1);d[n-k+i][s[n-k+i]]=0;
    }
}
void spfa()
{
    Node node;
    while(!q.empty())
    {
        node=q.front();q.pop();
        int u=node.u;int state=node.state;
        inq[u][state]=false;
        for(int p=head[u];p!=-1;p=edges[p].next)
        {
            int v=edges[p].v;
            if(d[v][state|s[v]]>d[u][state]+edges[p].w)
            {
                d[v][state|s[v]]=d[u][state]+edges[p].w;
                if(!inq[v][state|s[v]]&&state==(state|s[v]))
                {
                    inq[v][state]=true;
                    node.u=v;node.state=state;
                    q.push(node);
                }
            }
        }
    }
}
void Steiner_Tree()
{
    Node tmp;
    for(int j=0;j<N;++j)
    {
        for(int i=1;i<=n;++i)
        {
            for(int z=(j-1)&j;z;z=(z-1)&j)
              d[i][j]=min(d[i][j],d[i][z|s[i]]+d[i][(j-z)|s[i]]);
            if(d[i][j]<inf) {tmp.u=i;tmp.state=j;q.push(tmp);inq[i][j]=true;}
        }
        spfa();
    }
}