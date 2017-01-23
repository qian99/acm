struct Node
{
    int v,num;
};
vector<Node>query[maxn];
struct Edge
{
    int v,w,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int ans[10010];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int len[maxn],parents[maxn];
int n,m,k;
bool vis[maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void tarjan(int u,int fa)
{
    parents[u]=u;
    vis[u]=true;
    int sz=query[u].size();
    int v,anc;
    Node node;
    for(int i=0;i<sz;++i)
    {
        node=query[u][i];
        v=node.v;
        if(vis[v])
        {
            anc=Find(v);
            ans[node.num]=len[u]+len[v]-2*len[anc];
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].v;
        if(v==fa) continue;
        len[v]=len[u]+edges[k].w;
        tarjan(v,u);
        parents[v]=u;
    }
}