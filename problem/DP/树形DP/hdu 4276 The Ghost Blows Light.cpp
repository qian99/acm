#include <iostream>
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
const int maxt=500+10;
const int maxn=100+10;
struct Edge
{
    int v,dist;
};
vector<int>G[maxn];
vector<Edge>edges;
int dp[maxn][maxt],path[maxn],w[maxn];
int n,T,lt;
bool flag;
void ClearAll(int n)
{
    for(int i=0;i<=n;++i) G[i].clear();
    edges.clear();
    memset(dp,0,sizeof(dp));
}
void AddEdges(int u,int v,int dist)
{
    edges.push_back((Edge){v,dist});
    edges.push_back((Edge){u,dist});
    int m=edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
}
void find_path(int u,int fa,int step)
{
    if(u==n)
    {
        lt=step;
        flag=true;
        return ;
    }
    if(flag) return;
    Edge e;
    for(int i=0;i<G[u].size();++i)
    {
        e=edges[G[u][i]];
        if(e.v!=fa)
        {
            find_path(e.v,u,step+e.dist);
            if(flag)
            {
                edges[G[u][i]].dist=0;
                edges[G[u][i]^1].dist=0;
                return;
            }
        }
    }
}
void dfs(int u,int fa)
{
    Edge e;
    for(int i=0;i<G[u].size();++i)
    {
        e=edges[G[u][i]];
        if(e.v!=fa)
        {
            dfs(e.v,u);
            int ww=2*e.dist;
            for(int j=T;j>=ww;--j)
              for(int k=j-ww;k>=0;--k)
                dp[u][j]=max(dp[u][j],dp[u][k]+dp[e.v][j-k-ww]);
        }
    }
    for(int i=0;i<=T;++i)
       dp[u][i]+=w[u];
}
void solve()
{
    flag=false;
    find_path(1,-1,0);
    if(lt>T)
    {
        puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
        return;
    }
    T-=lt;
    dfs(1,-1);
    printf("%d\n",dp[1][T]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&T))
    {
        int a,b,c;
        ClearAll(n);
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b,c);
        }
        for(int i=1;i<=n;++i)
           scanf("%d",&w[i]);
        solve();
    }
    return 0;
}
