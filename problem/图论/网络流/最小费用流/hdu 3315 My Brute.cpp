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
const int maxn=2000+10;
const int maxm=100000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],p[maxn],nEdge;
bool inq[maxn];
void AddEdges(int from, int to,int cap,int cost)
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
        d[i]=-inf;
        inq[i]=false;
    }
    queue<int>q;
    d[s]=0;p[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap&&d[e.to]<d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                if(!inq[e.to]) {inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==-inf) return false;
    flow+=1;
    cost+=d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].cap-=1;
        edges[p[u]^1].cap+=1;
        u=edges[p[u]^1].to;
    }
    return true;
}
int H[maxn],P[maxn],A[maxn],B[maxn],V[maxn];
bool check(int x,int y)
{
    int H1=H[x],H2=P[y];
    int D1=A[x],D2=B[y];
    int turns=0;
    while(H1>0&&H2>0)
    {
        if(turns==0) H2-=D1;
        else H1-=D2;
        turns^=1;
    }
    return H1>H2;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=2*n+1;
        for(int i=1;i<=n;++i)
            scanf("%d",&V[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&H[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&P[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&A[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&B[i]);
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i+n,T,1,0);
            for(int j=1;j<=n;++j)
            {
                if(check(i,j))
                {
                    if(i==j) AddEdges(i,j+n,1,V[i]*100+1);
                    else AddEdges(i,j+n,1,V[i]*100);
                }
                else
                {
                    if(i==j) AddEdges(i,j+n,1,-V[i]*100+1);
                    else AddEdges(i,j+n,1,-V[i]*100);
                }
            }
        }
        int flow=0,cost=0;
        while(spfa(S,T,flow,cost));
        if(cost<=0) printf("Oh, I lose my dear seaco!\n");
        else
        {
            printf("%d %.3lf%%\n",cost/100,100.0*(cost%100)/n);
        }
    }
    return 0;
}
