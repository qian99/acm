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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=300+10;
const int maxm=100000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(int to=0,int cap=0,int cost=0,int next=0):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],a[maxn],p[maxn],nEdge,S,T;
bool inq[maxn];
int st[maxn],tt[maxn],C[maxn][maxn],D[maxn][maxn],E[maxn][maxn],F[maxn][maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(to,cap,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,-cost,head[to]);
    head[to]=nEdge;
}
int spfa(int &flow,int &cost)
{
    memset(inq,0,sizeof(inq));
    memset(d,0x3f,sizeof(d));
    queue<int>q;
    q.push(S);
    d[S]=0;a[0]=inf;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(d[e.to]>d[u]+e.cost&&e.cap)
            {
                d[e.to]=d[u]+e.cost;
                a[e.to]=min(a[u],e.cap);
                p[e.to]=k;
                if(!inq[e.to]) {inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[T]==inf) return false;
    flow+=a[T];
    cost+=a[T]*d[T];
    int u=T;
    while(u!=S)
    {
        edges[p[u]].cap-=a[T];
        edges[p[u]^1].cap+=a[T];
        u=edges[p[u]^1].to;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,K;
    while(~scanf("%d%d%d",&n,&m,&K))
    {
        if(n==0&&m==0&&K==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            scanf("%d%d",&st[i],&tt[i]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&C[i][j]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&D[i][j]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&E[i][j]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&F[i][j]);
        S=0,T=n*2+m+2;
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i+n,T,1,0);
            for(int j=1;j<=n;++j)
            {
                if(i!=j&&tt[i]+E[i][j]<tt[j])
                {
                    int c=max(tt[i]+E[i][j],st[j])-st[j];
                    c*=K;
                    AddEdges(i,n+j,1,c+F[i][j]);
                }
            }
        }
        AddEdges(S,n*2+m+1,m,0);
        for(int i=1;i<=m;++i)
        {
            AddEdges(n*2+m+1,n*2+i,1,0);
            for(int j=1;j<=n;++j)
            {
                if(C[j][i]<tt[j])
                {
                    int c=max(C[j][i],st[j])-st[j];
                    c*=K;
                    AddEdges(n*2+i,j+n,1,c+D[j][i]);
                }
            }
        }
        int flow=0,cost=0;
        while(spfa(flow,cost));
        if(flow!=n) printf("-1\n");
        else printf("%d\n",cost);

    }
    return 0;
}
