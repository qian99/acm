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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int dp[maxn][3];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0] = 1;
    dp[u][1] = dp[u][2] = 0;
    int minv = inf;
    int cnt = 0;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0] += min(dp[v][1],dp[v][0]);
        if(dp[v][2] == inf)
        {
            dp[u][1] = inf;
            cnt++;
        }
        if(!cnt) dp[u][1] += dp[v][2];
        if(cnt < 2) dp[u][2] += dp[v][2];
        minv = min(minv,dp[v][0] - dp[v][2]);
    }
    if(cnt < 2) dp[u][2] += minv;
    else dp[u][2] = inf;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u ,v;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        int ans = min(dp[1][0],dp[1][2]);
        printf("%d\n",ans);
        scanf("%d",&n);
        if(n == -1) break;
    }
    return 0;
}
