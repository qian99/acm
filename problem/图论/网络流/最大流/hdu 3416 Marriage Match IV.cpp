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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int maxm=100000+10;
struct EDGE
{
    int from,to,dist;
};
struct Edge
{
    int from,to,cap,flow;
};
struct HeapNode
{
    int d,u;
    bool operator < (const  HeapNode & a) const
    {
        return a.d<d;
    }
};
struct Dijkstra
{
    vector<EDGE>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int n,m;
    void AddEdges(int from,int to,int dist)
    {
        edges.push_back((EDGE){from,to,dist});
        m=edges.size();
        G[from].push_back(m-1);
    }
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void dijkstra(int s,int *d)
    {
        priority_queue<HeapNode>q;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;++i) d[i]=inf;
        d[s]=0;
        q.push((HeapNode){0,s});
        while(!q.empty())
        {
            HeapNode hp=q.top();q.pop();
            int u=hp.u;
            if(vis[u]) continue;
            vis[u]=true;
            for(int i=0;i<G[u].size();++i)
            {
                EDGE e=edges[G[u][i]];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
}slover;
struct Dinic
{
    vector<Edge>edges;
    vector<int>G[maxn];
    int d[maxn],cur[maxn];
    bool vis[maxn];
    int n,m,s,t;
    void clearAll(int n)
    {
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int cap)
    {
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int>q;
        d[s]=0;vis[s]=true;
        q.push(s);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to]=d[x]+1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x,int a)
    {
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int & i=cur[x];i<G[x].size();++i)
        {
            Edge e=edges[G[x][i]];
            if(d[e.to]==d[x]+1&&(f=DFS(e.to,min(a,e.cap-e.flow))>0))
            {
                edges[G[x][i]].flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s,int t)
    {
        this->s=s;this->t=t;
        int flow=0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,inf);
        }
        return flow;
    }
}dinic;
int dis1[maxn],dis2[maxn];
EDGE ee[maxm];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        slover.Init(n);
        dinic.clearAll(n);
        int s,t,w=0;
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            if(a==b) continue;
            ee[w++]=(EDGE){a,b,c};
            slover.AddEdges(a,b,c);
        }
        scanf("%d%d",&s,&t);
        slover.dijkstra(s,dis1);
        slover.Init(n);
        for(int i=0;i<w;++i) {slover.AddEdges(ee[i].to,ee[i].from,ee[i].dist);}
        slover.dijkstra(t,dis2);
        if(dis1[t]==inf)
        {
            printf("0\n");
            continue;
        }
        for(int i=0;i<w;++i)
        {
           if(dis1[ee[i].from]+dis2[ee[i].to]+ee[i].dist==dis1[t])
                   dinic.AddEdges(ee[i].from,ee[i].to,1);
        }
        int ans=dinic.MaxFlow(s,t);
        printf("%d\n",ans);
    }
    return 0;
}
