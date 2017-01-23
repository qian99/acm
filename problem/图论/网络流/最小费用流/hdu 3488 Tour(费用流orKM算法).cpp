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
const int maxn=400+10;
const int maxm=30000+10;
struct Edge
{
    int from,to,cap,flow,cost,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int co,int nx)
    {from=ff;to=tt;cap=cc;flow=fl;cost=co;next=nx;}
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],p[maxn],a[maxn];
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(from,to,cap,0,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,int &cost)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    d[s]=0;a[s]=inf;p[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                a[e.to]=min(a[u],e.cap-e.flow);
                if(!inq[e.to]){inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    flow+=a[t];
    cost+=a[t]*d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].flow+=a[t];
        edges[p[u]^1].flow-=a[t];
        u=edges[p[u]].from;
    }
    return true;
}
void mincost(int s,int t,int &flow,int &cost)
{
    flow=0,cost=0;
    while(spfa(s,t,flow,cost));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v+n,1,w);
        }
        int S=0,T=n*2+1;
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i+n,T,1,0);
        }
        int flow,cost;
        mincost(S,T,flow,cost);
        printf("%d\n",cost);
    }
    return 0;
}

