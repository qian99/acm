const int maxn=100+10;
int head[maxn];
bool vis[maxn];
int ans[maxn];
int n,m;
struct NODE
{
    int from;
    int to;
    bool operator < (const NODE & a) const
    {
        return (from==a.from&&to<a.to)||from<a.from;
    }
};
NODE edge[maxn];
void Init()
{
    for(int i=0;i<m;++i)
        cin>>edge[i].from>>edge[i].to;
    sort(edge,edge+m);
    memset(head,-1,sizeof(head));
    head[edge[0].from]=0;
    for(int i=1;i<m;++i)
      if(edge[i].from!=edge[i-1].from) head[edge[i].from]=i;
}



//链式前向星

const int maxn=100+10;
const int maxm=1000+10;
int head[maxn];
int n,m,nEdge;      //n为顶点数，m为边数，nEdge为存储的边的数量
                    //如果边是双向的，那么存储的边的数量就是2m
struct NODE
{
    int to;
    int next;
};
NODE edge[maxm<<1];
void addedges(int u,int v)       //将边(u,v)添加进去
{
    nEdge++;
    edge[nEdge].next=head[u];
    edge[nEdge].to=v;
    head[u]=nEdge;
}
void foreach()       //遍历边
{
    int i,k;
    for(i=1;i<=n;i++)
    {
        for(k=head[i];k!=-1;k=edge[k].next)
        {
            cout<<i<<" "<<edge[k].to<<endl;
        }
    }
}
void Init()
{
    nEdge=-1;
    memset(head,0xff,sizeof(head));
    int u,v;
    for(int i=0;i<m;++i)
    {
        cin>>u>>v;
        addedges(u,v);
        addedges(v,u);
    }
}