#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int maxm=3000000+10;
const int lev=15;
int ch[maxm][2],sum[maxm],size;
int root[maxn];
int Newnode(int val)
{
   size++;
   ch[size][0]=ch[size][1]=0;
   sum[size]=val;
   return size;
}
int Insert(int x,int val,int dep)
{
    int rt=Newnode(sum[x]+1);
    if(dep==-1) return rt;
    int d=(val>>dep)&1;
    ch[rt][d^1]=ch[x][d^1];
    ch[rt][d]=Insert(ch[x][d],val,dep-1);
    return rt;
}
int query(int x,int y,int val)
{
    int res=0;
    for(int i=lev;i>=0;--i)
    {
        int d=(val>>i)&1;
        int tmp=sum[ch[y][d^1]]-sum[ch[x][d^1]];
        if(tmp>0) res|=(1<<i);
        else d^=1;
        x=ch[x][d^1];y=ch[y][d^1];
    }
    return res;
}
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nx){v=vv;next=nx;}
}edges[maxn<<1];
int head[maxn],pa[maxn],father[maxn],nEdge,n,m;
vector<pair<int,int> >querys[maxn];
int ans[maxn],w[maxn],z[maxn];
bool vis[maxn];
void Init()
{
    ch[0][0]=ch[0][1]=sum[0]=size=0;
    memset(root,0,sizeof(root));
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    nEdge=-1;father[1]=0;
    for(int i=0;i<=n;++i) querys[i].clear();
}
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
    pa[u]=u;vis[u]=true;
    root[u]=Insert(root[father[u]],w[u],lev);
    int sz=querys[u].size();
    int v,pos,lca;
    for(int i=0;i<sz;++i)
    {
        v=querys[u][i].first;pos=querys[u][i].second;
        if(vis[v])
        {
            lca=Find(v);
            ans[pos]=max(query(root[lca],root[u],z[pos]),query(root[lca],root[v],z[pos]));
            ans[pos]=max(w[lca]^z[pos],ans[pos]);
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].v;
        if(v==fa) continue;
        father[v]=u;
        dfs(v,u);
        pa[v]=u;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        for(int i=1;i<=n;++i)
            scanf("%d",&w[i]);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&u,&v,&z[i]);
            querys[u].push_back(make_pair(v,i));
            querys[v].push_back(make_pair(u,i));
        }
        dfs(1,-1);
        for(int i=1;i<=m;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
