#pragma comment(linker, "/STACK:102400000,102400000")
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
const int maxn=200000+10;
const int maxm=500000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],cut[maxn],nEdge,n,m,S,T;
bool vis[maxn];
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS()
{
    for(int i=0;i<=n*2;++i) d[i]=-1;
    queue<int>q;
    q.push(S);
    d[S]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(d[e.to]==-1&&e.cap>e.flow)
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
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) return flow;
        }
    }
    d[u]=-1;
    return flow;
}
int calcut()
{
    for(int i=0;i<=n*2;++i) vis[i]=false;
    queue<int>q;
    int res=0,tot=0;
    cut[tot++]=S;vis[S]=true;
    while(tot)
    {
        while(tot) q.push(cut[--tot]);
        tot=0;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                Edge &e =edges[k];
                if(!vis[e.to]&&e.cap)
                {
                    if(e.cap==e.flow) cut[tot++]=e.to;
                    else if(e.cap>e.flow) {vis[e.to]=true;q.push(e.to);}
                }
            }
        }
        if(tot&&!vis[T]) res++;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n*2;++i) head[i]=-1;
        nEdge=-1;
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u+n,v,inf);
        }
        for(int i=0;i<n;++i)
            AddEdges(i,i+n,1);
        scanf("%d%d",&S,&T);
        if(head[S]!=-1) edges[head[S]].cap=inf;
        if(head[T]!=-1) edges[head[T]].cap=inf;
        T=T+n;
        int tot=0,flow=0;
        bool flag=true;
        flow=0;
        while(BFS())
            flow+=DFS(S,inf);
        if(flow==0) flag=false;
        else if(flow==1) tot=calcut();
        if(!flag) tot=n-2;
        printf("%d\n",tot+2);
    }
    return 0;
}
