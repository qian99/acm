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
const int maxn=1000+10;
int n,m;
struct Edge
{
    int from,to,dist;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode &a )const
    {
        return d>a.d;
    }
};
vector<Edge>edges;
vector<int>G[maxn];
bool vis[maxn];
int dis[maxn],dp[maxn];
void Init()
{
    for(int i=0;i<=n;++i)
      G[i].clear();
    edges.clear();
}
void addEdges(int from,int to,int dist)
{
    edges.push_back((Edge){from,to,dist});
    int temp=edges.size();
    G[from].push_back(temp-1);
}
void dijkstra(int s)
{
    priority_queue<HeapNode>q;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;++i) dis[i]=inf;
    dis[s]=0;
    q.push((HeapNode){0,s});
    while(!q.empty())
    {
        HeapNode hp=q.top();q.pop();
        int u=hp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            Edge e=edges[G[u][i]];
            if(dis[u]+e.dist<dis[e.to])
            {
                dis[e.to]=dis[u]+e.dist;
                q.push((HeapNode){dis[e.to],e.to});
            }
        }
    }
}
int f(int u,int e)
{
    if(u==e) return 1;
    if(dp[u]>0) return dp[u];
    dp[u]=0;
    for(int i=0;i<G[u].size();++i)
    {
        Edge x=edges[G[u][i]];
        if(dis[u]>dis[x.to])
        {
            dp[u]+=f(x.to,e);
        }
    }
    return dp[u];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        Init();
        scanf("%d",&m);
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            addEdges(a,b,c);
            addEdges(b,a,c);
        }
        dijkstra(2);
        memset(dp,0xff,sizeof(dp));
        int ans=f(1,2);
        printf("%d\n",ans);
    }
    return 0;
}
