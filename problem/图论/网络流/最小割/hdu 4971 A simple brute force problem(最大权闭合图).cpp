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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
const int maxm = 100000;
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
bool BFS(int S,int T)
{
    for(int i=0;i<=T;++i) d[i]=-1;
    queue<int>q;
    q.push(S);
    d[S]=0;
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
    return d[T]!=-1;
}
int DFS(int u,int a,int T)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge &e=edges[k];
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
int w[maxn],tw[maxn],val[maxn];
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;
stack<int>S;
vector<int>G[maxn],g[maxn],needs[maxn];
void dfs(int u)
{
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])
        {
            lowlink[u]=min(lowlink[u],pre[v]);
        }
    }
    if(lowlink[u]==pre[u])
    {
        scc_cnt++;
        for(;;)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
int solve(int n,int m)
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=m;++i)
    {
        if(!pre[i]) dfs(i);
    }
    memset(val,0,sizeof(val));
    for(int i = 1; i<= m;++i) g[i].clear();
    for(int u = 1;u <= m;++u)
    {
        val[sccno[u]] += tw[u];
        for(int i = 0;i < G[u].size();++i)
        {
            int v=G[u][i];
            if(sccno[u] != sccno[v])
            {
                g[sccno[u]].push_back(sccno[v]);
            }
        }
    }
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    int S = 0 ,T = scc_cnt + n +1;
    for(int i = 1;i <= n;++i)
    {
//        cout<<needs[i].size()<<endl;
        for(int j = 0;j < (int)needs[i].size();++j)
        {
            int v = needs[i][j];
            AddEdges(sccno[v]+n,i,inf);
        }
    }
    for(int i = 1;i <= scc_cnt;++i)
    {

        for(int j = 0;j < (int)g[i].size();++j)
        {
            AddEdges(i+n,g[i][j]+n,inf);
        }
    }
    int sum = 0;
    for(int i = 1;i <= n;++i)
    {
        AddEdges(i,T,w[i]);
        sum += w[i];
    }

    for(int i = 1;i <= scc_cnt;++i)
    {
//        sum += val[i];
        AddEdges(S,i+n,val[i]);
    }
    while(BFS(S,T))
        sum-=DFS(S,inf,T);
    return sum;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;++i)
            scanf("%d",&w[i]);
        for(int i = 1;i <= m ;++ i)
            scanf("%d",&tw[i]);
        for(int i = 1;i <= n;++i)
        {
            int k,v;
            scanf("%d",&k);
            needs[i].clear();
            for(int j = 0;j < k;++j)
            {
                scanf("%d",&v);
                v++;
                needs[i].push_back(v);
            }
        }
        for(int i = 1;i <= m;++i) G[i].clear();
        for(int i = 1;i <= m;++i)
        {
            for(int j = 1;j <= m;++j)
            {
                int v;
                scanf("%d",&v);
                if(v) G[j].push_back(i);
            }
        }
        int ans = solve(n,m);
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}