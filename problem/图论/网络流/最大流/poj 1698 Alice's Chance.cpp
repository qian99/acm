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
const int maxn=10000+10;
const int maxm=100000+10;
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
bool BFS(int s,int t)
{
    memset(d,0xff,sizeof(d));
    queue<int>q;
    q.push(s);
    d[s]=0;
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
    return d[t]!=-1;
}
int DFS(int u,int a,int t)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge& e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap),t))>0)
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
int F[25][10],D[25],W[25];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S,T,xa,xb,mxw=0,sum=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=7;++j)
                scanf("%d",&F[i][j]);
            scanf("%d%d",&D[i],&W[i]);
            mxw=max(mxw,W[i]);
            sum+=D[i];
        }
        S=0;T=mxw*7+mxw*7*n+n+1;
        xa=mxw*7;xb=xa+mxw*7*n;
        for(int i=1;i<=mxw;++i)
            for(int j=1;j<=7;++j)
            {
                AddEdges(S,(i-1)*7+j,1);
                for(int k=1;k<=n;++k)
                {
                    if(F[k][j])
                        AddEdges((i-1)*7+j,xa+(k-1)*mxw*7+(i-1)*7+j,1);
                }
            }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=W[i];++j)
                for(int k=1;k<=7;++k)
                    AddEdges(xa+(i-1)*mxw*7+(j-1)*7+k,xb+i,1);
            AddEdges(xb+i,T,D[i]);
        }
        int flow=0;
        while(BFS(S,T))
            flow+=DFS(S,inf,T);
        if(flow==sum) puts("Yes");
        else puts("No");
    }
    return 0;
}
