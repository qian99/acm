#include <iostream>
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
const int maxn=100000+10;
const int dep=17;
struct Edge
{
    int v,dist;
};
vector<Edge>edges;
vector<int>G[maxn];
int d[maxn],w[maxn],fa[maxn][dep+1];
bool vis[maxn];
void clearAll(int n)
{
    for(int i=0;i<=n;++i) G[i].clear();
    edges.clear();
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
}
void AddEdges(int u,int v,int dist)
{
    edges.push_back((Edge){v,dist});
    edges.push_back((Edge){u,dist});
    int m=edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
}
void bfs(int s,int n)
{
    d[s]=0;w[s]=0;
    queue<int>q;
    q.push(s);
    Edge e;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            e=edges[G[u][i]];
            if(!vis[e.v])
            {
                d[e.v]=d[u]+1;
                w[e.v]=w[u]+e.dist;
                fa[e.v][0]=u;
                q.push(e.v);
            }
        }
    }
    for(int i=1;i<=dep;++i)
      for(int j=1;j<=n;++j)
        fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int x,int y)
{
    if(x==y) return x;
    if(d[x]>d[y]) swap(x,y);
    for(int i=dep;i>=0;--i)
      if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x) return x;
    if(d[y]>d[x]) y=fa[y][0];
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
    int t,tcase=0;
    scanf("%d",&t);
    int n,q;
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&q);
        clearAll(n);
        int x,y,z;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            AddEdges(x,y,z);
        }
        bfs(1,n);
        scanf("%d%d%d",&x,&y,&z);
        printf("Case #%d:\n",tcase);
        int u,v,anc,anc2,ans1,ans2;
        while(q--)
        {
            scanf("%d%d",&u,&v);
            anc=lca(u,v);
            ans1=w[u]+w[v]-2*w[anc];
            anc=lca(u,x);
            anc2=lca(v,y);
            ans2=w[u]+w[x]-2*w[anc]+w[v]+w[y]-2*w[anc2]+z;
            anc=lca(u,y);
            anc2=lca(v,x);
            ans2=min(ans2,w[u]+w[y]-2*w[anc]+w[v]+w[x]-2*w[anc2]+z);
            if(ans1>ans2) ans1=ans1-ans2;
            else ans1=0;
            printf("%d\n",ans1);
        }
    }
    return 0;
}
