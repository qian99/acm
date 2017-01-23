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
const int maxn=3000+10;
const int maxm=20000+100;
const int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int id[55][55],val[55][55],color[55][55];
int head[maxn],d[maxn],cur[maxn],nEdge,n,m;
bool vis[maxn];
struct Edge
{
    int from,to,cap,flow,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int nn)

{from=ff;to=tt;cap=cc;flow=fl;next=nn;};
}edges[maxm<<1];
void AddEdge(int from, int to, int cap)
{
    edges[++nEdge]=Edge(from,to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int S,int T)
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    vis[S]=true;
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
int DFS(int u,int a,int T)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),T))>0)
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
        for(int i=0;i<=T;++i) cur[i]=head[i];
        flow+=DFS(S,inf,T);
    }
    return flow;
}
inline bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
    m=n;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int turns=0,cnt=0,sum=0;
        for(int i=0;i<n;++i)
        {
            turns=i&1;
            for(int j=0;j<m;++j)
            {
                scanf("%d",&val[i][j]);
                sum+=val[i][j];
                color[i][j]=turns;
                turns^=1;
                id[i][j]=++cnt;
            }
        }
        int S=0,T=n*m+1,x,y;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                if(color[i][j]) AddEdge(id[i][j],T,val[i][j]);
                else
                {
                    AddEdge(S,id[i][j],val[i][j]);
                    for(int k=0;k<4;++k)
                    {
                        x=i+dir[k][0];
                        y=j+dir[k][1];
                        if(check(x,y))
                            AddEdge(id[i][j],id[x][y],inf);
                    }
                }
            }
        }
        sum-=Maxflow(S,T);
        printf("%d\n",sum);
    }
    return 0;
}

