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
const int maxm=4000+10;
struct Edge
{
    int from,to,cap,flow,next;
    double cost;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,double co,int nx)
    {from=ff;to=tt;cap=cc;flow=fl;cost=co;next=nx;}
}edges[maxm<<1];
int head[maxn],a[maxn],p[maxn],nEdge;
bool inq[maxn];
double d[maxn];
void AddEdges(int from,int to,int cap,double cost)
{
    edges[++nEdge]=Edge(from,to,cap,0,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,double &cost)
{
    memset(inq,0,sizeof(inq));
    memset(d,0,sizeof(d));
    a[s]=inf;p[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap>e.flow&&d[e.to]<d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                a[e.to]=min(a[u],e.cap-e.flow);
                p[e.to]=k;
                if(!inq[e.to]){inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==0) return false;
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
void mincost(int s,int t)
{
    int flow=0;double cost=0;
    while(spfa(s,t,flow,cost)) ;
}
int basicp[maxn],w[maxn],matrix[maxn][maxn],res[maxn];
double getpoint(int i,int x)
{
    return (4.0-3.0*(100-x)*(100-x)/1600.0)*w[i];
}
double solve(int S,int m)
{
    double ans=0;
    memset(res,0,sizeof(res));
    for(int k=head[S];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        res[e.to]+=e.flow;
    }
    for(int i=1;i<=m;++i)
    {
        res[i]+=basicp[i];
        if(res[i]<60) return 0;
        ans+=getpoint(i,res[i]);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,m;
    while(~scanf("%d%d%d",&n,&k,&m))
    {
        if(n==0&&k==0&&m==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=m;++i)
            scanf("%d",&w[i]);
        for(int i=1;i<=m;++i)
            scanf("%d",&basicp[i]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&matrix[i][j]);
        int S=0,T=n+m+1,sum=0;
        for(int i=1;i<=m;++i)
        {
            if(basicp[i]<60) AddEdges(S,i,60-basicp[i],1e6);
            int j=max(basicp[i],60)+1;
            for(;j<=100;++j)
                AddEdges(S,i,1,getpoint(i,j)-getpoint(i,j-1));
            for(j=1;j<=n;++j)
                if(matrix[j][i]) AddEdges(i,m+j,k,0);
            sum+=w[i];
        }
        for(int i=1;i<=n;++i)
            AddEdges(m+i,T,k,0);
        mincost(S,T);
        double ans=solve(S,m)/sum;
        printf("%.6lf\n",ans);
    }
    return 0;
}

