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
const int maxn = 100 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int A[maxn],B[maxn],dp[maxn][maxn][2],tmp[maxn][2];
int head[maxn],nEdge,n;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    memset(dp[u],0x3f,sizeof(dp[u]));
    dp[u][u][0] = A[u];
    dp[u][u][1] = B[u];
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs(v,u);
        memset(tmp,0x3f,sizeof(tmp));
        for(int i = 1;i <= n;++i)
        {
            if(dp[v][i][0] == inf) continue;
            for(int j = 1;j <= n;++j)
            {
                if(dp[u][j][0] != inf)
                {
                    if(A[i] < A[j])
                        tmp[i][0] = min(tmp[i][0],dp[v][i][0] + dp[u][j][0] - A[j] + A[j]/2);
                    else
                        tmp[j][0] = min(tmp[j][0],dp[v][i][0] + dp[u][j][0] - A[i] + A[i]/2);
                }
                if(dp[u][j][1] != inf)
                    tmp[j][1] = min(tmp[j][1],dp[v][i][0] + dp[u][j][1]);
            }
        }
        for(int i = 1;i <= n;++i)
        {
            if(dp[v][i][1] == inf) continue;
            for(int j = 1;j <= n;++j)
            {
                if(dp[u][j][0] != inf)
                    tmp[j][0] = min(tmp[j][0],dp[u][j][0] + dp[v][i][1]);
                if(dp[u][j][1] != inf)
                {
                    if(B[i] < B[j])
                        tmp[i][1] = min(tmp[i][1],dp[u][j][1] + dp[v][i][1] - B[j] + B[j]/2);
                    else
                        tmp[j][1] = min(tmp[j][1],dp[u][j][1] + dp[v][i][1] - B[i] + B[i]/2);
                }
            }
        }
        for(int i = 1;i <= n;++i)
        {
            dp[u][i][0] = tmp[i][0];
            dp[u][i][1] = tmp[i][1];
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i = 1;i <= n;++i)
            scanf("%d",&A[i]);
        for(int i = 1;i <= n;++i)
            scanf("%d",&B[i]);
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u,v;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        int ans = inf;
        for(int i = 1;i <= n;++i)
        {
            ans = min(ans,dp[1][i][0]);
            ans = min(ans,dp[1][i][1]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
