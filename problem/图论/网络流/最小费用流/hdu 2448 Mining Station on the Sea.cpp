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
const int maxn=500+10;
const int maxm=500000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],p[maxn],d[maxn],a[maxn],nEdge;
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(to,cap,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,int &cost)
{
    for(int i=0;i<=t;++i)
    {
        d[i]=inf;
        inq[i]=false;
    }
    queue<int>q;
    q.push(s);
    d[s]=0;a[s]=inf;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                a[e.to]=min(a[u],e.cap);
                if(!inq[e.to]) {inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    flow+=a[t];
    cost+=d[t]*a[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].cap-=a[t];
        edges[p[u]^1].cap+=a[t];
        u=edges[p[u]^1].to;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k,p;
    while(~scanf("%d%d%d%d",&n,&m,&k,&p))
    {
        int S=0,T=n+m+1;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&v);
            AddEdges(S,v,1,0);
            AddEdges(i+m,T,1,0);
        }
        for(int i=0;i<k;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,inf,w);
            AddEdges(v,u,inf,w);
        }
        for(int i=0;i<p;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(v,u+m,1,w);
        }
        int flow=0,cost=0;
        while(spfa(S,T,flow,cost));
        printf("%d\n",cost);
    }
    return 0;
}
