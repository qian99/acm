#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=40000+10;
const int dep=17;
struct Edge
{
    int v,w,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int fa[maxn][dep+1],d[maxn],len[maxn];
int n,m,k;
bool vis[maxn];
void bfs()
{
    memset(vis,0,sizeof(vis));
    memset(fa,0,sizeof(fa));
    d[1]=0;vis[1]=true;len[1]=0;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(vis[v]) continue;
            vis[v]=true;
            d[v]=d[u]+1;
            len[v]=len[u]+edges[k].w;
            fa[v][0]=u;
            q.push(v);
        }
    }
    for(int i=1;i<=dep;++i)
      for(int j=1;j<=n;++j)
        fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int x,int y)
{
    if(x==y) return x;
    if(d[x]<d[y]) swap(x,y);
    for(int i=dep;i>=0;i--)
      if(d[fa[x][i]]>d[y]) x=fa[x][i];
    if(fa[x][0]==y) return y;
    if(d[x]>d[y]) x=fa[x][0];
    for(int i=dep;i>=0;--i)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[5];
    while(~scanf("%d%d",&n,&m))
    {
        int u,v,w;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d%s",&u,&v,&w,str);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        bfs();
        scanf("%d",&k);
        while(k--)
        {
            scanf("%d%d",&u,&v);
            int anc=lca(u,v);
            int ans=len[u]+len[v]-2*len[anc];
            printf("%d\n",ans);
        }
    }
    return 0;
}
