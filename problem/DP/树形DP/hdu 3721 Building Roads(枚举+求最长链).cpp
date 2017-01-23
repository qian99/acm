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
const int maxn = 2500 + 10;
struct Edge
{
    int u,v,w,next;
    Edge(int u = 0,int v = 0,int w = 0,int next = 0):u(u),v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],dp[maxn][2],sons[maxn][2],nEdge,mv;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(u,v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(v,u,w,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0] = dp[u][1] = 0;
    sons[u][0] = sons[u][1] = -1;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs(v,u);
        int len = dp[v][0] + edges[k].w;
        if(len > dp[u][0])
        {
            dp[u][1] = dp[u][0];
            sons[u][1] = sons[u][1];
            dp[u][0] = len;
            sons[u][0] = v;
        }
        else if(len > dp[u][1])
        {
            dp[u][1] = len;
            sons[u][1] = v;
        }
    }
}
void dfs2(int u,int fa,int pre)
{
    int maxlen = 0;
    maxlen = max(pre,dp[u][0]);
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        if(sons[u][0] == v)
            dfs2(v,u,max(pre ,dp[u][1])+ edges[k].w);
        else
            dfs2(v,u,max(pre ,dp[u][0])+ edges[k].w);
    }
    mv = min(mv,maxlen);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u,v,w;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            u++;v++;
            AddEdges(u,v,w);
        }
        int ans = inf,mx,x,y;
        for(int i = 0;i <= nEdge;i += 2)
        {
            u = edges[i].u;
            v = edges[i].v;
            w = edges[i].w;
            mv = inf;
            dfs(u,v);
            dfs2(u,v,0);
            x = mv;
            mv = inf;
            dfs(v,u);
            dfs2(v,u,0);
            y = mv;
            mx = 0;
            for(int j = 1;j <= n;++j)
                mx = max(mx,dp[j][0] + dp[j][1]);
            mx = max(mx,x + y + w);
            if(mx < ans) ans = mx;
        }
        if(n <= 1) ans = 0;
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}

