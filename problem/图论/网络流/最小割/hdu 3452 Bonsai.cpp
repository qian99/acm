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
const int maxn=1000+10;
const int maxm=5000+10;
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge,n,S,T;
vector<pair<int,int> >G[maxn];
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,head[to]);
    head[to]=nEdge;
}
bool BFS()
{
    memset(d,0xff,sizeof(d));
    queue<int>q;
    q.push(S);
    d[S]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(d[e.to]==-1&&e.cap)
            {
                d[e.to]=d[u]+1;
                q.push(e.to);
            }
        }
    }
    return d[T]!=-1;
}
int DFS(int u,int a)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge &e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap)))>0)
        {
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            flow+=f;a-=f;
            if(a==0) return flow;
        }
    }
    d[u]=-1;
    return flow;
}
void build(int u,int fa)
{
    int child=0;
    for(int i=0;i<(int)G[u].size();++i)
    {
        int v=G[u][i].first;
        if(v==fa) continue;
        child++;
        build(v,u);
        AddEdges(u,v,G[u][i].second);
    }
    if(child==0) AddEdges(u,T,inf);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int r;
    while(~scanf("%d%d",&n,&r))
    {
        if(n==0&&r==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<=n;++i) G[i].clear();
        int u,v,w;
        S=r,T=n+1;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back(make_pair(v,w));
            G[v].push_back(make_pair(u,w));
        }
        build(r,-1);
        int flow=0;
        while(BFS())
            flow+=DFS(S,inf);
        if(n==1) flow=0;
        printf("%d\n",flow);
    }
    return 0;
}
