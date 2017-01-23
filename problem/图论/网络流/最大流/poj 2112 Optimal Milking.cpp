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
const int maxn=200+55;
const int maxm=10000+10;
int dis[maxn][maxn],d[maxn],cur[maxn];
int K,C,M,N,S,T;
int head[maxn],nEdge;
bool vis[maxn];
struct Edge
{
    int to,next,cap,flow;
    Edge (){};
    Edge (int v,int nx,int ca,int fl){to=v;next=nx;cap=ca;flow=fl;}
}edges[maxm<<1];
void AddEdge(int from,int to,int cap)
{
    nEdge++;
    edges[nEdge]=Edge(to,head[from],cap,0);
    head[from]=nEdge++;
    edges[nEdge]=Edge(from,head[to],0,0);
    head[to]=nEdge;
}
void floyd()
{
    for(int k=1;k<=N;++k)
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
bool BFS()
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    d[S]=0;vis[S]=true;
    queue<int>q;
    q.push(S);
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
    return vis[T];
}
int DFS(int u,int a)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(e.cap-e.flow,a)))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=T;++i) cur[i]=head[i];
        flow+=DFS(S,inf);
    }
    return flow;
}
void buildGragh(int lim)
{
    nEdge=-1;
    memset(head,0xff,sizeof(head));
    S=0,T=N+1;
    for(int i=1;i<=C;++i)
    {
        AddEdge(S,K+i,1);
        for(int j=1;j<=K;++j)
           if(dis[K+i][j]<=lim) AddEdge(K+i,j,1);
    }
    for(int i=1;i<=K;++i)
        AddEdge(i,T,M);
}
int solve()
{
    int L=0,R=inf;
    int val;
    while(L<R)
    {
        int m=(L+R)>>1;
        buildGragh(m);
        val=Maxflow();
        if(val==C)
            R=m;
        else L=m+1;
    }
    return R;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&K,&C,&M);
    N=C+K;
    for(int i=1;i<=N;++i)
      for(int j=1;j<=N;++j)
      {
          scanf("%d",&dis[i][j]);
          if(dis[i][j]==0&&i!=j) dis[i][j]=inf;
      }
    floyd();
    int ans=solve();
    printf("%d\n",ans);
    return 0;
}

