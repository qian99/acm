#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int maxm=300000+10;
struct Edge
{
    int to,cap,next;
    Edge(int to=0,int cap=0,int next=0):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
bool vis[maxn];
int n,m,K;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int S,int T)
{
    for(int i = 0;i <= T; ++i) d[i] = -1;
    d[S]=0;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[e.to]==-1&&e.cap)
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
        Edge & e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap),T))>0)
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
int sccno[maxn],stk[maxn],top;
bool dfs(int u,int fa,int last)
{
    vis[u] = true;
    stk[top++] = u;
    for(int k = head[u];k != -1;k=edges[k].next)
    {
        int v = edges[k].to;
        if(v == fa || edges[k].cap == 0) continue;
        if(!vis[v])
        {
            if(dfs(v,u,edges[k^1].cap)) return true;
        }
        else if (!sccno[v])
            return true;
    }
    if(!last)
    {
        while(true)
        {
            int x = stk[--top];
            sccno[x] = true;
            if(x == u) break;
        }
    }
    return false;
}
int row[maxn],col[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=n+m+1,w;
        int sum1=0,sum2=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&row[i]);
            sum1+=row[i];
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&col[i]);
            sum2+=col[i];
        }
        bool flag = false;
        for(int i = 1;i <= n;++i)
            if(9*m < row[i]) flag = true;
        for(int i = 1;i <= m;++i)
            if(9*n < col[i]) flag = true;
        printf("Case #%d: ",++tcase);
        if(sum1!=sum2 || flag) printf("So naive!\n");
        else
        {
            for(int i = 1;i <= n;++i)
            {
                AddEdges(S,i,row[i]);
                for(int j=1;j<=m;++j)
                    AddEdges(i,j+n,9);
            }
            for(int i = 1;i <= m;++i)
                AddEdges(i+n,T,col[i]);
            int flow=0;
            while(BFS(S,T)) flow+=DFS(S,inf,T);
            if(flow!=sum1) printf("So naive!\n");
            else
            {
                memset(vis,0,sizeof(vis));
                memset(sccno,0,sizeof(sccno));
                top = 0;
                flag = dfs(T,-1,0);
                if(flag) printf("So young!\n");
                else printf("So simple!\n");
            }
        }
    }
    return 0;
}
