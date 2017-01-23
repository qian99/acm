#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
const int maxn=30000+10;
const int maxm=60000+10;
struct Edge
{
    int v,w,next;
    Edge(int v=0,int w=0,int next=0):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge,n,m,K;
int d[maxn];
bool vis[maxn];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
struct HeapNode
{
    int d,u;
    HeapNode(int d=0,int u=0):d(d),u(u){}
    bool operator < (const HeapNode & a) const
    {
        return a.d<d;
    }
};
struct Dijkstra
{
    int n,m;
    vector<Edge>E;
    vector<int>G[maxn];
    bool vis[maxn];
    int dis[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) G[i].clear();
        E.clear();
    }
    void AddEdge(int from,int to,int dist)
    {
        E.push_back(Edge(to,dist));
        m=E.size();
        G[from].push_back(m-1);
    }
    void dijkstra(int s)
    {
        priority_queue<HeapNode>q;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<=n;++i) dis[i]=inf;
        dis[s]=0;
        HeapNode hp=HeapNode(0,s);
        q.push(hp);
        while(!q.empty())
        {
           hp=q.top();q.pop();
           int u=hp.u;
           if(vis[u]) continue;
           vis[u]=true;
           for(int i=0;i<(int)G[u].size();++i)
           {
               Edge e=E[G[u][i]];
               if(dis[e.v]>dis[u]+e.w)
               {
                   dis[e.v]=dis[u]+e.w;
                   q.push(HeapNode(dis[e.v],e.v));
               }
           }
        }
    }
}dij;
void build(int u)
{
    vis[u]=true;
    for(int i=0;i<(int)dij.G[u].size();++i)
    {
        Edge e=dij.E[dij.G[u][i]];
        if(!vis[e.v]&&dij.dis[e.v]==dij.dis[u]+e.w)
        {
            AddEdges(u,e.v,e.w);
            build(e.v);
        }
    }
}
int ansmx,wroot,wnum,tot_node,cnt;
ll ansnum,num[maxn];
int childs[maxn],flag[maxn],val[maxn],wsw[maxn],S[maxn];
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    nEdge=-1;
    ansmx=ansnum=0;
    memset(childs,0,sizeof(childs));
    memset(flag,0,sizeof(flag));
    memset(val,0xff,sizeof(val));
    memset(d,0,sizeof(d));
    memset(num,0,sizeof(num));
}
void dfs(int u,int fa)
{
    childs[u]=1;
    int mx=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||flag[v]) continue;
        dfs(v,u);
        childs[u]+=childs[v];
        if(childs[v]>mx) mx=childs[v];
    }
    mx=max(mx,tot_node-childs[u]);
    if(mx<wnum)
    {
        wnum=mx;
        wroot=u;
    }
}
void DFS(int u,int fa)
{
    S[cnt++]=u;
    if(d[u]==K)
    {
        if(wsw[u]>ansmx)
            ansmx=wsw[u],ansnum=1;
        else if(wsw[u]==ansmx)
            ansnum++;
    }
    else if(d[u]<K&&val[K-d[u]+1]>0)
    {
        int tmp=wsw[u]+val[K-d[u]+1];
        if(tmp>ansmx)
            ansmx=tmp,ansnum=num[K-d[u]+1];
        else if(tmp==ansmx)
            ansnum+=num[K-d[u]+1];
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||flag[v]) continue;
        d[v]=d[u]+1;
        wsw[v]=wsw[u]+edges[k].w;
        DFS(v,u);
    }
}
void solve(int u,int tx)
{
    if(tx==1) return ;
    wnum=tot_node=tx;
    dfs(u,-1);
    flag[wroot]=1;
    cnt=0;
    d[wroot]=1;wsw[wroot]=0;
    for(int k=head[wroot];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(flag[v]) continue;
        d[v]=2;wsw[v]=edges[k].w;
        int last=cnt;
        DFS(v,wroot);
        for(int j=last;j<cnt;++j)
        {
            if(val[d[S[j]]]<wsw[S[j]]) val[d[S[j]]]=wsw[S[j]],num[d[S[j]]]=1;
            else if(val[d[S[j]]]==wsw[S[j]]) num[d[S[j]]]++;
        }
    }
    for(int i=0;i<cnt;++i)
        val[d[S[i]]]=-1;
    for(int k=head[wroot];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(flag[v]||childs[v]==1) continue;
        solve(v,childs[v]);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&K);
        int u,v,w;
        dij.init(n);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            dij.AddEdge(u,v,w);
            dij.AddEdge(v,u,w);
        }
        dij.dijkstra(1);
        for(int i=1;i<=n;++i)
            sort(dij.G[i].begin(),dij.G[i].end());
        Init();
        build(1);
        solve(1,n);
        printf("%d %I64d\n",ansmx,ansnum);
    }
    return 0;
}
