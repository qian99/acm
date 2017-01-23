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
const int maxn = 20000 + 10;
struct Edge
{
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],q[maxn],pa[maxn],flag[maxn],dp[maxn],nEdge;
int addval[maxn][3],ans;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
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
void cal(int x)
{
    int tail = 0,u,v;
    q[tail++] = x;
    pa[x] = 0;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        memset(addval[u],0,sizeof(addval[u]));
        for(int k = head[u]; k != -1 ;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            pa[v] = u;
            q[tail++] = v;
        }
    }
    for(int i = tail - 1;i >= 0 ;--i)
    {
        u = q[i];
        addval[u][0] = 1;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            for(int j = 0;j < 3;++j)
                addval[u][(j+edges[k].w)%3] += addval[v][j];
        }
    }
}
void solve(int x)
{
    int root = findroot(x);
    flag[root] = true;
    memset(addval[root],0,sizeof(addval[root]));
    int tmp[3] = {0};
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(flag[v]) continue;
        cal(v);
        memset(tmp,0,sizeof(tmp));
        for(int i = 0;i < 3;++i)
        {
            int j = (i+edges[k].w)%3;
            tmp[j] += addval[v][i];
        }
        ans += tmp[0]*2;
        for(int i = 0;i < 3;++i)
            for(int j = 0;j < 3;++j)
                if((i + j)%3 == 0)
                    ans += addval[root][i]*tmp[j]*2;
        for(int i = 0;i < 3;++i)
            addval[root][i] += tmp[i];
    }
    for(int k = head[root];k != -1;k = edges[k].next)
        if(!flag[edges[k].v]) solve(edges[k].v);
}
int gcd(int a,int b) { return b == 0?a:gcd(b,a%b);}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u,v,w;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        memset(flag,0,sizeof(flag));
        ans = 0;
        solve(1);
        v = n*n;
        ans = ans + n;
        w = gcd(ans,v);
        ans /= w;
        v /= w;
        printf("%d/%d\n",ans,v);
    }
    return 0;
}

