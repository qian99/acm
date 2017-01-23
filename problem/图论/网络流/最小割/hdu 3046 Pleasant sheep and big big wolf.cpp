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
const int maxn=200+10;
const int maxm=200000+10;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn*maxn],d[maxn*maxn],nEdge;
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
        Edge e=edges[k];
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
int MaxFlow(int s,int t)
{
    int flow=0;
    while(BFS(s,t))
        flow+=DFS(s,inf,t);
    return flow;
}
int mat[maxn][maxn],id[maxn][maxn],n,m;
inline bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=m;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        int cnt=0,S=0,T=n*m+1;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&mat[i][j]);
                id[i][j]=++cnt;
            }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                int dx,dy;
                for(int k=0;k<4;++k)
                {
                    dx=i+dirx[k];
                    dy=j+diry[k];
                    if(check(dx,dy))
                        AddEdges(id[i][j],id[dx][dy],1);
                }
                if(mat[i][j]==2) AddEdges(S,id[i][j],inf);
                if(mat[i][j]==1) AddEdges(id[i][j],T,inf);
            }
        int ans=MaxFlow(S,T);
        printf("Case %d:\n",++tcase);
        printf("%d\n",ans);
    }
    return 0;
}
