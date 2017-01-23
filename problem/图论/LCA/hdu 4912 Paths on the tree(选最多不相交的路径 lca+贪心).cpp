#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
struct Node
{
    int u,v,id;
    Node(int u=0,int v=0,int id=0):u(u),v(v),id(id) {}
}node[maxn];
int head[maxn],nEdge;
int LCA[maxn],pa[maxn],d[maxn];
bool vis[maxn];
vector<pair<int,int> >querys[maxn];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    pa[u]=u;
    pair<int,int>pii;
    for(int i=0;i<(int)querys[u].size();++i)
    {
        pii=querys[u][i];
        if(d[pii.first]==-1) continue;
        LCA[pii.second]=Find(pii.first);
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs(v,u);
        pa[v]=u;
    }
}
bool cmp(Node a,Node b)
{
    int u=LCA[a.id];
    int v=LCA[b.id];
    return d[u]>d[v];
}
void Init(int n)
{
    memset(vis,0,sizeof(vis));
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(d,0xff,sizeof(d));
    for(int i=0;i<=n;++i)
        querys[i].clear();
}
void tour(int u)
{
    vis[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(vis[v]||d[v]<d[u]) continue;
        tour(v);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        Init(n);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            querys[u].push_back(make_pair(v,i));
            querys[v].push_back(make_pair(u,i));
            node[i].u=u;node[i].v=v;
            node[i].id=i;
        }
        d[1]=0;
        dfs(1,-1);
        sort(node,node+m,cmp);
        int cnt=0;
        for(int i=0;i<m;++i)
        {
            if(!vis[node[i].u]&&!vis[node[i].v])
            {
                cnt++;
                tour(LCA[node[i].id]);
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
