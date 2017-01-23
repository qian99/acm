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
const int maxn=1100+10;
const int maxm=20000+10;
struct Edge
{
    int from,to,cap,flow,next;
}edges[maxm<<1];
int head[maxn],ft[maxn],nEdge,n,m;
int d[maxn],pa[maxn];
bool vis[maxn];
void AddEdge(int from,int to,int cap)
{
    nEdge++;edges[nEdge].from=from;edges[nEdge].to=to;
    edges[nEdge].cap=cap;edges[nEdge].flow=0;
    edges[nEdge].next=head[from];head[from]=nEdge;
    nEdge++;edges[nEdge].from=to;edges[nEdge].to=from;
    edges[nEdge].cap=edges[nEdge].flow=0;
    edges[nEdge].next=head[to];head[to]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(ft,0,sizeof(ft));
    nEdge=-1;
}
bool BFS(int s,int t)
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    d[s]=0;vis[s]=true;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}
int DFS(int u,int a,int t)
{
    if(u==t||a==0) return a;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&e.cap>e.flow)
        {
            pa[e.to]=k;
            int tmp=DFS(e.to,min(a,e.cap-e.flow),t);
            if(tmp) return tmp;
        }
    }
    return 0;
}
int Maxflow(int s,int t)
{
    int flow=0;
    while(BFS(s,t))
    {
        int f=DFS(s,inf,t);
        flow+=f;
        int u=t;
        while(u!=s)
        {
            edges[pa[u]].flow+=f;
            edges[pa[u]^1].flow-=f;
            u=edges[pa[u]].from;
        }
    }
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int s,t;
    scanf("%d%d",&m,&n);
    Init();
    s=0;t=n+m+1;
    int tmp,k;
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&tmp);
        AddEdge(s,i,tmp);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&k);
        for(int j=0;j<k;++j)
        {
            scanf("%d",&tmp);
            if(ft[tmp]) AddEdge(ft[tmp]+m,i+m,inf);
            else
            {
                AddEdge(tmp,i+m,inf);
                ft[tmp]=i;
            }
        }
        scanf("%d",&tmp);
        AddEdge(i+m,t,tmp);
    }
    int ans=Maxflow(s,t);
    printf("%d\n",ans);
    return 0;
}
