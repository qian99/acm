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
const int maxn = 200000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],d[maxn],pa[maxn],S[maxn],nEdge;
int rp[maxn],vis[maxn],cnt,ux,uy,ans,m;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
bool check(int limit)
{
    cnt++;
    int a = rp[limit + 1];
    int b = rp[m - limit];
    if(limit + 1 >= m - limit)
    {
        a = rp[m/2];
        b = rp[m/2 + 1];
    }
    int tail = 0,u,v;
    d[a] = d[b] = 0;
    S[tail++] = a;
    S[tail++] = b;
    vis[a] = vis[b] = cnt;
    for(int i = 0;i < tail;++i)
    {
        u = S[i];
        if(d[u] > limit) return false;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(vis[v] == cnt) continue;
            vis[v] = cnt;
            pa[v] = u;
            d[v] = d[u] + 1;
            S[tail++] = v;
        }
    }
    if(limit < ans)
    {
        ans = limit;
        ux = a;
        uy = b;
    }
    return true;
}
void solve()
{
    pa[1] = -1;
    int tail = 0,maxd = 0,mpos,u,v;
    S[tail++] = 1;
    d[1] = 0;
    for(int i = 0;i < tail;++i)
    {
        u = S[i];
        if(d[u] > maxd)
        {
            maxd = d[u];
            mpos = u;
        }
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u]) continue;
            d[v] = d[u] + 1;
            pa[v] = u;
            S[tail++] = v;
        }
    }
    pa[mpos] = -1;
    tail = 0;
    S[tail++] = mpos;
    d[mpos] = 0;
    maxd = 0;
    for(int i = 0;i < tail;++i)
    {
        u = S[i];
        if(d[u] > maxd)
        {
            maxd = d[u];
            mpos = u;
        }
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u]) continue;
            pa[v] = u;
            d[v] = d[u] + 1;
            S[tail++] = v;
        }
    }
    m = 0;
    u = mpos;
    while(u != -1)
    {
        rp[++m] = u;
        u = pa[u];
    }
    int L = 0,R = tail,mid;
    ans = inf;
    cnt = 0;
    memset(vis,0,sizeof(vis));
    while(L < R)
    {
        mid = (L + R)>>1;
        if(check(mid)) R = mid;
        else L = mid + 1;
    }
    check(L);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int n,u,v;
        scanf("%d",&n);
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        solve();
        printf("%d %d %d\n",ans,ux,uy);
    }
    return 0;
}
