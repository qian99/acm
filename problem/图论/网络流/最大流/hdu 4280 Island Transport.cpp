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
//#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int maxm=200000+10;
struct Edge
{
    int to,cap,next;
    Edge(){};
    Edge(int tt,int cc,int nx)
    {to=tt;cap=cc;next=nx;};
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],cur[maxn],n,m,S,T;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
}
bool BFS(int S,int T)
{
    memset(d,0xff,sizeof(d));
    queue<int>q;
    q.push(S);
    d[S]=0;
    int v;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].to;
            if(d[v]==-1&&edges[k].cap>0)
            {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    return d[T]!=-1;
}
int DFS(int u,int a)
{
    if(u==T||a==0) return a;
    int flow=0,f,v;
    for(int &k =cur[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].to;
        if(d[v]==d[u]+1&&(f=DFS(v,min(a,edges[k].cap)))>0)
        {
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow()
{
    int flow=0;
    while(BFS(S,T))
    {
        for(int i=0;i<=n;++i) cur[i]=head[i];
        flow+=DFS(S,inf);
    }
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d%d",&n,&m);
        int sval=inf,tval=-inf;
        int x,y,z;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            if(x<sval)
            {
                sval=x;
                S=i;
            }
            if(x>tval)
            {
                tval=x;
                T=i;
            }
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            AddEdges(x,y,z);
            AddEdges(y,x,z);
        }
        int ans=Maxflow();
        printf("%d\n",ans);
    }
    return 0;
}

