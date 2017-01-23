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
const int maxn=60000+10;
const int maxm=200000+10;
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int S,int T)
{
    for(int i=0;i<=T;++i) d[i]=-1;
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
int DFS(int u,int a,int T)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge &e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap),T))>0)
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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w,sum=0;
        int S=0,T=n+m+1;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w);
            AddEdges(i,T,w);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(i+n,u,inf);
            AddEdges(i+n,v,inf);
            AddEdges(S,i+n,w);
            sum+=w;
        }
        while(BFS(S,T))
            sum-=DFS(S,inf,T);
        printf("%d\n",sum);
    }
    return 0;
}
