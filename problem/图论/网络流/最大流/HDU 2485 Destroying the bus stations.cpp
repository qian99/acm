#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=3000;
const int maxm=5000;
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
    bool operator < (const HeapNode & a) const
    {
        return a.d<d;
    }
};
struct Dijkstra
{
    int n,m;
    vector<EDGE>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    void clearAll(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i)
          G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int dist)
    {
        edges.push_back((EDGE){from,to,dist});
        m=edges.size();
        G[from].push_back(m-1);
    }
    void dijkstra(int s,int *d)
    {
        for(int i=1;i<=n;++i) d[i]=inf;
        memset(vis,0,sizeof(vis));
        priority_queue<HeapNode>q;
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
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    int d[maxn],cur[maxn];
    bool vis[maxn];
    void clearAll(int n)
    {
        for(int i=0;i<=n;++i)
          G[i].clear();
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
        q.push(s);
        d[s]=0;vis[s]=1;
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    vis[e.to]=1;
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
        for(int& i=cur[x];i<G[x].size();++i)
        {
            Edge e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
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
    int Maxflow(int s,int t)
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
EDGE ee[maxm];
int dist1[maxn],dist2[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        if(n==0&&m==0&&k==0) break;
        if(n<3)
        {
            printf("0\n");
            continue;
        }
        slover.clearAll(n);
        dinic.clearAll(n*2);
        int x,y;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            slover.AddEdges(x,y,1);
            ee[i].from=x;ee[i].to=y;
        }
        slover.dijkstra(1,dist1);
        slover.clearAll(n);
        for(int i=0;i<m;++i)
           slover.AddEdges(ee[i].to,ee[i].from,1);
        slover.dijkstra(n,dist2);
        for(int i=2;i<n;++i)
           dinic.AddEdges(i*2,i*2+1,1);
        for(int i=0;i<m;++i)
        {
            EDGE e=ee[i];
            if(dist1[e.from]+dist2[e.to]<k)
            {
                if(e.from==1) dinic.AddEdges(e.from,e.to*2,1);
                else if(e.to==n) dinic.AddEdges(e.from*2+1,n*2,1);
                else dinic.AddEdges(e.from*2+1,e.to*2,1);
            }
        }
        int ans=dinic.Maxflow(1,2*n);
        printf("%d\n",ans);
    }
    return 0;
}
