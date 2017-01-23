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
const int maxn=2555;
const int maxm=100000+10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm];
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
        Edge &e=edges[k];
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
int val[55][55],id[55][55];
bool vis[55][55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        memset(vis,0,sizeof(vis));
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=n*m+1,cnt=0,sum=0;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&val[i][j]);
                sum+=val[i][j];
                id[i][j]=++cnt;
            }
        int x,y;
        while(k--)
        {
            scanf("%d%d",&x,&y);
            vis[x][y]=true;
            if((x+y)&1) AddEdges(S,id[x][y],inf);
            else AddEdges(id[x][y],T,inf);
        }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                if(!vis[i][j])
                {
                    if((i+j)&1) AddEdges(S,id[i][j],val[i][j]);
                    else AddEdges(id[i][j],T,val[i][j]);
                }
                if((i+j)&1)
                {
                    for(int k=0;k<4;++k)
                    {
                        x=i+dirx[k];
                        y=j+diry[k];
                        if(x>=1&&x<=n&&y>=1&&y<=m)
                            AddEdges(id[i][j],id[x][y],(val[i][j]&val[x][y])<<1);
                    }
                }
            }
        int flow=0;
        while(BFS(S,T))
            flow+=DFS(S,inf,T);
        printf("%d\n",sum-flow);
    }
    return 0;
}
