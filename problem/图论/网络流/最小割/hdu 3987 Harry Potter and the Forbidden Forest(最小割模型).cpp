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
const int maxn=1000+10;
const int maxm=200000+10;
struct Edge
{
    int from,to,cap,flow,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int nx)
    {from=ff;to=tt;cap=cc;flow=fl;next=nx;}
}edges[maxm<<1];
int head[maxn],d[maxn],cur[maxn],nEdge,n,m;
bool vis[maxn];
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(from,to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int S,int T)
{
    memset(d,0,sizeof(d));
    memset(vis,0,sizeof(vis));
    vis[S]=true;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
    return vis[T];
}
int DFS(int u,int a,int T)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),T))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return  flow;
}
int Maxflow(int S,int T)
{
    int flow=0;
    while(BFS(S,T))
    {
        for(int i=0;i<=n;++i) cur[i]=head[i];
        flow+=DFS(S,inf,T);
    }
    return flow;
}
int Findcut(int S,int T)
{
    for(int i=0;i<nEdge;i+=2)
    {
        if(edges[i].cap==edges[i].flow)
            edges[i].cap=1;
        else edges[i].cap=inf;
        edges[i].flow=edges[i^1].flow=0;
    }
    return Maxflow(S,T);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,c,d;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&c,&d);
            AddEdges(u,v,c);
            if(d) AddEdges(v,u,c);
        }
        Maxflow(0,n-1);
        int ans=Findcut(0,n-1);
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}

