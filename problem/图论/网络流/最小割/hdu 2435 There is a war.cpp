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
const int maxn=100+10;
const int maxm=100000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
bool vis[maxn],flag[maxn][maxn];
vector<int>cut;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int S,int T)
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
            if(d[e.to]==-1&&e.cap>e.flow)
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
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),T))>0)
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
int MaxFlow(int S,int T)
{
    int flow=0;
    while(BFS(S,T))
        flow+=DFS(S,inf,T);
    return flow;
}
void getcut(int n)
{
    memset(vis,0,sizeof(vis));
    cut.clear();
    queue<int>q;
    q.push(1);
    vis[1]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
    for(int i=2;i<n;++i)
        if(vis[i])
        for(int k=head[i];k!=-1;k=edges[k].next)
        {
            if(k&1) continue;
            if(!vis[edges[k].to]&&edges[k].to!=1&&edges[k].to!=n)
                cut.push_back(k);
        }
    for(int i=2;i<n;++i)
        if(vis[i])
        for(int j=2;j<n;++j)
        {
            if(i==j) continue;
            if(!flag[i][j]&&!vis[j])
            {
                AddEdges(i,j,0);
                cut.push_back(nEdge-1);
            }
        }
}
void clearflow()
{
    for(int i=0;i<=nEdge;++i)
        edges[i].flow=0;
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
        memset(flag,0,sizeof(flag));
        nEdge=-1;
        int u,v,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            AddEdges(u,v,c);
            flag[u][v]=true;
        }
        int ans=MaxFlow(1,n);
        getcut(n);
        int size=cut.size(),last;
        for(int i=0;i<size;++i)
        {
            if(i) edges[cut[i-1]].cap=last;
            last=edges[cut[i]].cap;
            edges[cut[i]].cap=inf;
            clearflow();
            ans=max(ans,MaxFlow(1,n));
        }
        printf("%d\n",ans);
    }
    return 0;
}
