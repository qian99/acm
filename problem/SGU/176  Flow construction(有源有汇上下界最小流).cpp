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
const int maxm=100000+10;
struct Edge
{
    int v,next,cap,flow;
    Edge (){};
    Edge(int vv,int nx,int cc,int ff) {v=vv;next=nx;cap=cc;flow=ff;}
}edges[maxm<<1];
int head[maxn],bcnt[maxm],nEdge;
int cur[maxn],d[maxn],ins[maxn],outs[maxn],N;
bool vis[maxn];
void AddEdge(int u,int v,int cap)
{
    edges[++nEdge]=Edge(v,head[u],cap,0);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v],0,0);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(bcnt,0,sizeof(bcnt));
    memset(ins,0,sizeof(ins));
    memset(outs,0,sizeof(outs));
    nEdge=-1;
}
bool BFS(int S,int T)
{
    memset(vis,0,sizeof(vis));
    memset(d,0x3f,sizeof(d));
    vis[S]=true;d[S]=0;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e =edges[k];
            if(!vis[e.v]&&e.cap>e.flow)
            {
                d[e.v]=d[u]+1;
                vis[e.v]=true;
                q.push(e.v);
            }
        }
    }
    return vis[T];
}
int DFS(int u,int T,int a)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.v]==d[u]+1&&(f=DFS(e.v,T,min(a,e.cap-e.flow)))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow(int S,int T)
{
    int flow=0;
    while(BFS(S,T))
    {
        for(int i=0;i<=N;++i) cur[i]=head[i];
        flow+=DFS(S,T,inf);
    }
    return flow;
}
int f(int l,int r,int sum)
{
    int res=-1,m;
    while(l<=r)
    {
        m=(l+r)>>1;
        edges[nEdge^1].cap=m;
        if(Maxflow(0,N)==sum)
        {
            res=m;
            r=m-1;
        }
        else l=m+1;
        for(int i=0;i<=nEdge;++i)
            edges[i].flow=0;
    }
    if(res!=-1)
    {
        for(int i=0;i<=nEdge;++i)
            edges[i].flow=0;
        edges[nEdge^1].cap=res;
        Maxflow(0,N);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n,m,sum=0;
    int u,v,z,c;
    scanf("%d%d",&n,&m);
    N=n+1;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d%d",&u,&v,&z,&c);
        bcnt[i]=z*c;
        if(c) {ins[v]+=z,outs[u]+=z;}
        AddEdge(u,v,z-z*c);
    }
    for(int i=1;i<=n;++i)
    {
        sum+=ins[i];
        if(ins[i]) AddEdge(0,i,ins[i]);
        if(outs[i]) AddEdge(i,N,outs[i]);
    }
    AddEdge(n,1,inf);
     //使用下面注释掉的二分得到最终结果
    //int ans=f(0,10000000,sum);
    if(Maxflow(0,N)!=sum)
    {
        printf("Impossible\n");
        return 0;
    }
    int ans=edges[nEdge-1].flow;
    edges[nEdge].cap=edges[nEdge^1].cap=0;
    edges[nEdge].flow=edges[nEdge^1].flow=0;
    int tmp=Maxflow(n,1);
    ans-=tmp;
    if(ans<0)
    {
        for(int i=0;i<=nEdge;++i)
            edges[i].flow=0;
        Maxflow(0,N);
        ans=0;
    }
    printf("%d\n",ans);
    for(int i=0;i<m;++i)
    {
        if(i) printf(" ");
        printf("%d",edges[i*2].flow+bcnt[i]);
    }
    printf("\n");
    return 0;
}
