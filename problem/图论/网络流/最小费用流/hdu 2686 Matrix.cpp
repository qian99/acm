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
int head[maxn],d[maxn],p[maxn],a[maxn],nEdge;
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
    queue<int>q;
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[s]=0;p[s]=0;a[s]=inf;
    q.push(s);
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
                a[e.to]=min(a[u],e.cap);
                p[e.to]=k;
                if(!inq[e.to]) {inq[e.to]=false;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    flow+=a[t];
    cost+=a[t]*d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].cap-=a[t];
        edges[p[u]^1].cap+=a[t];
        u=edges[p[u]^1].to;
    }
    return true;
}
void Mincost(int s,int t,int &flow,int &cost)
{
    flow=cost=0;
    while(spfa(s,t,flow,cost));
}
int val[55][55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=n*n-1;
        int res=0,id,dx,dy;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
            {
                scanf("%d",&val[i][j]);
                id=i*n+j;
                if(id==S) {res+=val[i][j];continue;}
                if(id==T) {res+=val[i][j];continue;}
                dx=i;dy=j+1;
                if(dy!=n) AddEdges(id+n*n,dx*n+dy,1,0);
                dx=i+1;dy=j;
                if(dx!=n) AddEdges(id+n*n,dx*n+dy,1,0);
                AddEdges(id,id+n*n,1,-val[i][j]);
            }
        AddEdges(S,1,1,0);
        AddEdges(S,n,1,0);
        int flow,cost;
        Mincost(S,T,flow,cost);
        res-=cost;
        printf("%d\n",res);
    }
    return 0;
}
