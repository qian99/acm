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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
const int maxm=10000+10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={-1,0,1,0};
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
bool vis[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(to,cap,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,-cost,head[to]);
    head[to]=nEdge;
}
int dfs(int u,int a,int t,int &cost)
{
    if(u==t)
    {
        cost+=a*d[t];
        return a;
    }
    vis[u]=true;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(e.cap&&d[e.to]==d[u]+e.cost&&!vis[e.to])
        {
            f=dfs(e.to,min(a,e.cap),t,cost);
            flow+=f;
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
bool changes(int n)
{
    int mind=inf;
    for(int i=0;i<=n;++i)
    {
        if(!vis[i]) continue;
        for(int k=head[i];k!=-1;k=edges[k].next)
            if(!vis[edges[k].to]&&edges[k].cap)
                mind=min(mind,d[i]+edges[k].cost-d[edges[k].to]);
    }
    if(mind==inf) return false;
    for(int i=0;i<=n;++i)
        if(!vis[i]) d[i]+=mind;
    return true;
}
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int mat[111][111],n,m,x,y;
int a[111],b[111];
int cal(int v[],int n,int c)
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int S=0,T=n+1;
    for(int i=0;i<n;++i)
    {
        AddEdges(S,i+1,v[i],0);
        AddEdges(i+1,T,c,0);
        if(i>0) AddEdges(i+1,i,inf,x);
        if(i<n-1) AddEdges(i+1,i+2,inf,x);
    }
    int flow=0,cost=0;
    memset(d,0x3f,sizeof(d));
    d[S]=0;
    while(true)
    {
        memset(vis,0,sizeof(vis));
        flow+=dfs(S,inf,T,cost);
        if(!changes(T)) break;
    }
    return cost;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        scanf("%d%d",&x,&y);
        int sum=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                scanf("%d",&mat[i][j]);
                sum+=mat[i][j];
                a[i]+=mat[i][j];
                b[j]+=mat[i][j];
            }
        int d=n*m/gcd(n,m);
        int ans=sum*y,tmp;
        for(int i=d;i<=sum;i+=d)
        {
            tmp=(sum-i)*y;
            if(tmp>=ans) continue;
            tmp+=cal(a,n,i/n);
            if(tmp>=ans) continue;
            tmp+=cal(b,m,i/m);
            if(tmp<ans) ans=tmp;
        }
        printf("%d\n",ans);
    }
    return 0;
}
