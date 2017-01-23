//求最大流与流量最大的增广路的比值
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
const int maxm=100000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],cur[maxn],d[maxn],nEdge;
int n,m,S,T,maxa;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
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
            Edge e=edges[k];
            if(d[e.to]==-1&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                q.push(e.to);
            }
        }
    }
    return d[T]!=-1;
}
int DFS(int u,int a,int v)
{
    if(u==T||a==0)
    {
        maxa=max(maxa,v);
        return a;
    }
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),min(v,e.cap)))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int MaxFlow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=n;++i) cur[i]=head[i];
        flow+=DFS(S,inf,inf);
    }
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&tcase,&n,&m,&S,&T);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            AddEdges(u,v,c);
        }
        maxa=-1;
        double ans=(double)MaxFlow()/maxa;
        printf("%d %.3lf\n",tcase,ans);
    }
    return 0;
}
