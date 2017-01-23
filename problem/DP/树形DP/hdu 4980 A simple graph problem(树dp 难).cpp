/*
	dp[u][i]结点u有i条向上的路径，它的子树都已经被覆盖，此时最小的花费
*/
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
const int maxn = 500 + 10;
struct Edge
{
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int tmp[maxn][maxn],dp[maxn][maxn],cnt[maxn],drop_cost;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    memset(dp[u],0x3f,sizeof(dp[u]));
    dp[u][0] = 0;
    dp[u][1] = drop_cost;
    cnt[u] = 1;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs(v,u);
        cnt[u] += cnt[v];
        for(int i = 0;i <= cnt[u] + 2;++i)
            for(int j = 0;j <= cnt[v] + 2;++j)
                tmp[i][j] = inf;
        for(int i = cnt[u];i >= 0;--i)
            for(int j = cnt[v];j >= 0;--j)
            {
                if(j > 0)
                    tmp[i][j] = dp[u][i] + dp[v][j] + j*edges[k].w;
                if(tmp[i+1][j+1] != inf)
                    tmp[i][j] = min(tmp[i][j],tmp[i+1][j+1] - drop_cost);
            }
        for(int i = cnt[u];i >= 0;--i)
        {
            dp[u][i] = inf;
            for(int j = 0;j <= cnt[v] && j <= i;++j)
                dp[u][i] = min(dp[u][i],tmp[i - j][j]);
        }

    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    int n;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        scanf("%d%d",&n,&drop_cost);
        int u,v,w;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u+1,v+1,w);
        }
        dfs(1,-1);
        printf("Case #%d: %d\n",++tcase,dp[1][0]);
    }
    return 0;
}
