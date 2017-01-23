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
const int maxn=200+10;
const int maxm=100000+10;
const int maxv=1000000;
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
int g[maxn][maxn];
void Init(int n)
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(g,0x3f,sizeof(g));
    for(int i=0;i<=n;++i) g[i][i]=0;
}
void floyd(int n)
{
    for(int k=0;k<=n;++k)
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        if(!n&&!m&&!k) break;
        Init(n);
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            g[u][v]=g[v][u]=min(g[u][v],w);
        }
        floyd(n);
        int S=0,T=n*2+3;
        AddEdges(S,1,k,0);
        for(int i=1;i<=n;++i)
        {
            if(g[0][i]!=inf) AddEdges(1,i+1,1,g[0][i]);
            for(int j=i+1;j<=n;++j)
                if(g[i][j]!=inf) AddEdges(i+n+1,j+1,1,g[i][j]);
            AddEdges(i+1,i+n+1,1,-maxv);
            AddEdges(i+n+1,T,1,g[i][0]);
        }
        int flow=0,cost=0;
        while(spfa(S,T,flow,cost));
        cost=cost+n*maxv;
        printf("%d\n",cost);
    }
    return 0;
}
