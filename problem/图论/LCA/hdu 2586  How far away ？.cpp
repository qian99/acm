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
typedef long long ll;
const int dep=18;
const int maxn=40000+10;
struct Edge
{
    int v,dist;
};
vector<int>G[maxn];
vector<Edge>edges;
int d[maxn],len[maxn],fa[maxn][dep];
bool vis[maxn];
void AddEdges(int u,int v,int dist)
{
    edges.push_back((Edge){v,dist});
    edges.push_back((Edge){u,dist});
    int m=edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
}
void bfs(int s)
{
    memset(vis,0,sizeof(vis));
    d[s]=0;len[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            Edge e=edges[G[u][i]];
            if(!vis[e.v])
            {
                fa[e.v][0]=u;
                d[e.v]=d[u]+1;
                len[e.v]=len[u]+e.dist;
                q.push(e.v);
            }
        }
    }
}
int lca(int x,int y)
{
    if(d[x]>d[y]) swap(x,y);
    for(int i=dep-1;i>=0;--i)
       if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x) return x;
    if(d[y]>d[x]) y=fa[y][0];
    for(int i=dep-1;i>=0;--i)
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
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,q,a,b,c;
        scanf("%d%d",&n,&q);
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b,c);
        }
        memset(fa,0,sizeof(fa));
        bfs(1);
        for(int i=1;i<dep;++i)
           for(int j=1;j<=n;++j)
             fa[j][i]=fa[fa[j][i-1]][i-1];
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&a,&b);
            int f=lca(a,b);
            int ans=len[a]+len[b]-2*len[f];
            printf("%d\n",ans);
        }
    }
    return 0;
}
