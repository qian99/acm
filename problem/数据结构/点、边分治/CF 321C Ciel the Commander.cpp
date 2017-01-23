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
const int maxn = 100000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],q[maxn],pa[maxn],flag[maxn],dp[maxn],nEdge;
char color[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
int findroot(int x)
{
    int tail = 0,u,v;
    q[tail++] = x;
    pa[x] = 0;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            pa[v] = u;
            q[tail++] = v;
        }
    }
    int minv = inf,root = -1,mx;
    for(int i = tail - 1;i >= 0;--i)
    {
        u = q[i];
        dp[u] = 1;mx = 0;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            dp[u] += dp[v];
            if(dp[v] > mx) mx = dp[v];
        }
        mx = max(mx,tail - dp[u]);
        if(mx < minv)
        {
            minv = mx;
            root = u;
        }
    }
    return root;
}
void solve(int x,char c)
{
    int root = findroot(x);
    color[root] = c;
    flag[root] = 1;
    for(int k = head[root];k != -1; k = edges[k].next)
    {
        int v = edges[k].v;
        if(flag[v]) continue;
        solve(edges[k].v,c + 1);
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
    int u,v;
    for(int i = 1;i < n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    solve(1,'A');
    for(int i = 1;i <= n;++i)
        printf("%c ",color[i]);
    puts("");
    return 0;
}

