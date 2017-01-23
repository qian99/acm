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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int d[maxn][maxn],to[maxn][maxn],degree[maxn],n,m;
int head[maxn],nEdge;
double dp[maxn][maxn];
bool vis[maxn][maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
void bfs(int s)
{
    memset(d[s],0x3f,sizeof(d[s]));
    queue<int>q;
    d[s][s] = 0;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            int v = edges[k].v;
            if(d[s][v] == inf)
            {
                d[s][v] = d[s][u] + 1;
                q.push(v);
            }
        }
    }
}
void precal()
{
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
        {
            if(i == j)
                to[i][j] = i;
            else
            {
                to[i][j] = -1;
                for(int k = head[i];k != -1;k = edges[k].next)
                {
                    int v = edges[k].v;
                    if(to[i][j] == -1) to[i][j] = v;
                    else if(d[j][v] < d[j][to[i][j]])
                        to[i][j] = v;
                    else if(d[j][v] == d[j][to[i][j]])
                        to[i][j] = min(to[i][j],v);
                }
            }
        }
}
double f(int s,int t)
{
    if(s == t) return 0;
    if(vis[s][t]) return dp[s][t];
    vis[s][t] = true;
    dp[s][t] = 0;
    int x = to[to[s][t]][t];
    if(x == t)
        return dp[s][t] = 1;
    dp[s][t] += (f(x,t) + 1)/degree[t];
    for(int k = head[t];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        dp[s][t] += (f(x,v) + 1)/degree[t];
    }
    return dp[s][t];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        memset(vis,0,sizeof(vis));
        memset(degree,0,sizeof(degree));
        int s,t,u,v;
        scanf("%d%d",&s,&t);
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
            degree[u]++;
            degree[v]++;
        }
        for(int i = 1;i <= n;++i)
            degree[i]++;
        for(int i = 1;i <= n;++i)
            bfs(i);
        precal();
        double ans = f(s,t);
        printf("%.3lf\n",ans);
    }
    return 0;
}
