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
const int maxm=100000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],a[maxn],p[maxn],nEdge;
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
            Edge &e=edges[k];
            if(e.cap&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                a[e.to]=min(a[u],e.cap);
                if(!inq[e.to]) {inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]>0) return false;
    cost+=d[t]*a[t];
    flow+=a[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].cap-=a[t];
        edges[p[u]^1].cap+=a[t];
        u=edges[p[u]^1].to;
    }
    return true;
}
int g[55][55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d%d",&n,&m);
        int S=0,T=n+m+1;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&g[i][j]);
        int w,sn=0,sm=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w);
            sn+=w;
            AddEdges(S,i,w,-100000);
            for(int j=1;j<=m;++j)
                AddEdges(i,j+n,1,g[i][j]);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&w);
            sm+=w;
            AddEdges(i+n,T,w,-100000);
        }
        for(int i=1;i<=m;++i)
            AddEdges(i+n,T,inf,0);
        for(int i=1;i<=n;++i)
            AddEdges(S,i,inf,0);
        int flow=0,cost=0;
        while(spfa(S,T,flow,cost));
        cost+=100000*(sn+sm);
        printf("%d\n",cost);
    }
    return 0;
}