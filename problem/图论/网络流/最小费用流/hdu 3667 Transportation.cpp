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
const int maxn=100+10;
const int maxm=30000+10;
int k;
struct Edge
{
    int from,to,cap,flow,cost;
    int next;
};
struct MCFC
{
    int head[maxn],nEdge;
    Edge edges[maxm<<1];
    int m,n,s,t;
    int d[maxn],inq[maxn],p[maxn],a[maxn];
    void Init(int n)
    {
        this->n=n;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
    }
    void AddEdges(int from,int to,int cap,int cost)
    {
        nEdge++;edges[nEdge].from=from;edges[nEdge].to=to;
        edges[nEdge].cap=cap;edges[nEdge].flow=0;edges[nEdge].cost=cost;
        edges[nEdge].next=head[from];head[from]=nEdge;
        nEdge++;edges[nEdge].from=to;edges[nEdge].to=from;
        edges[nEdge].cap=0;edges[nEdge].flow=0;edges[nEdge].cost=-cost;
        edges[nEdge].next=head[to];head[to]=nEdge;
    }
    bool BellmanFord(int s,int t,int & flow,int & cost)
    {
        memset(inq,0,sizeof(inq));
        for(int i=0;i<=n;++i) d[i]=inf;
        d[s]=0;p[s]=0;inq[s]=1;a[s]=inf;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            inq[u]=0;
            for(int i=head[u];i!=-1;i=edges[i].next)
            {
                Edge e=edges[i];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
                {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=i;
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]) {q.push(e.to);inq[e.to]=1;}
                }
            }
        }
        if(d[t]==inf) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }
    void Mincost(int s,int t,int &flow,int &cost)
    {
        flow=0,cost=0;
        while(BellmanFord(s,t,flow,cost));
    }
}mcfc;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        mcfc.Init(n);
        int u,v,a,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&a,&c);
            for(int j=1;j<=c;++j)
                mcfc.AddEdges(u,v,1,(2*j-1)*a);
        }
        mcfc.AddEdges(0,1,k,0);
        int flow,cost;
        mcfc.Mincost(0,n,flow,cost);
        if(flow<k)
          printf("-1\n");
        else printf("%d\n",cost);
    }
    return 0;
}
