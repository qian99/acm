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
const int maxn=100+10;
const int maxm=10000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
};
struct Dinic
{
    int head[maxn],cur[maxn],d[maxn],nEdge,S,T,n;
    Edge edges[maxm<<1];
    queue<int>q;
    void Init(int S,int T,int n)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        this->S=S;this->T=T;
        this->n=n;
    }
    void AddEdges(int from,int to,int cap)
    {
        edges[++nEdge]=Edge(to,cap,0,head[from]);
        head[from]=nEdge;
        edges[++nEdge]=Edge(from,0,0,head[to]);
        head[to]=nEdge;
    }
    bool BFS()
    {
        memset(d,0xff,sizeof(d));
        d[S]=0;
        q.push(S);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                Edge e=edges[k];
                if(d[e.to]==-1&&e.cap>e.flow)
                {
                    d[e.to]=d[u]+1;
                    q.push(e.to);
                }
            }
        }
        return d[T]!=-1;
    }
    int DFS(int u,int a)
    {
        if(u==T||a==0) return a;
        int flow=0,f;
        for(int &k=cur[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
            {
                edges[k].flow+=f;
                edges[k^1].flow-=f;
                flow+=f;a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int MaxFlow()
    {
        int flow=0;
        while(BFS())
        {
            for(int i=0;i<=n;++i) cur[i]=head[i];
            flow+=DFS(S,inf);
        }
        return flow;
    }
    void clearflow()
    {
        for(int i=0;i<=nEdge;++i)
            edges[i].flow=0;
    }
}dinic;
int ancient[15],cost[15],cnt;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int u,v,w,p,S=0,T=n+1;
        dinic.Init(S,T,n+1);
        cnt=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w);
            dinic.AddEdges(S,i,w);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&w,&p);
            if(p<0)
            {
                dinic.AddEdges(u,v,inf);
                dinic.AddEdges(u,T,w);
            }
            else if(p==0)
                dinic.AddEdges(u,v,inf);
            else
            {
                dinic.AddEdges(u,v,1);
                ancient[cnt]=dinic.nEdge-1;
                cost[cnt++]=w;
            }
        }
        int maxv=0,mincost=inf,N=(1<<cnt),tmp,flow;
        for(int i=0;i<N;++i)
        {
            tmp=0;
            for(int j=0;j<cnt;++j)
            {
                if(i&(1<<j))
                {
                    tmp+=cost[j];
                    dinic.edges[ancient[j]].cap=inf;
                }
                else dinic.edges[ancient[j]].cap=1;
            }
            dinic.clearflow();
            flow=dinic.MaxFlow();
            if(flow>maxv)
            {
                maxv=flow;
                mincost=tmp;
            }
            else if(flow==maxv)
                mincost=min(mincost,tmp);
        }
        if(maxv==0) printf("Poor Heaven Empire\n");
        else printf("%d %d\n",maxv,mincost);
    }
    return 0;
}
