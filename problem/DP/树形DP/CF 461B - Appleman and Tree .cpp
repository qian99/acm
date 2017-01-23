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
const int maxn = 100000+10;
const int mod = 1000000007;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<2];
int head[maxn],color[maxn],tcol[maxn],nEdge;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
ll dp[maxn],del[maxn];
void dfs(int u,int fa)
{
    if(color[u])
    {
        dp[u] = 1;
        del[u] = 0;
        tcol[u] = 1;
    }
    else
    {
        dp[u] = 0;
        del[u] = 1;
        tcol[u] = 0;
    }
    for(int k = head[u];k!=-1;k=edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs(v,u);
        if(!tcol[v]) continue;
        tcol[u] += tcol[v];
        if(color[u])
        {
            dp[u] = dp[u]*(dp[v]+del[v])%mod;
        }
        else
        {
            dp[u] = dp[u]*(dp[v]+del[v])%mod + del[u]*dp[v]%mod;
            dp[u] %= mod;
            del[u] = del[u]*(dp[v]+del[v])%mod;
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    int u;
    for(int i = 2;i <= n;++i)
    {
        scanf("%d",&u);
        u++;
        AddEdges(u,i);
    }
    for(int i = 1;i <= n;++i)
        scanf("%d",&color[i]);
    dfs(1,-1);
    printf("%I64d\n",dp[1]);
    return 0;
}