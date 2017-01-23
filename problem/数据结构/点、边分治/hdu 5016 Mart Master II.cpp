#include<iostream>
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
typedef long long ll;
const int maxn = 100000 + 10;
struct Edge
{
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxn<<1];
struct Node
{
    int D,u;
    Node(int D = 0,int u = 0):D(D),u(u) {}
    bool operator < (const Node & a) const
    {
        return (a.D == D && u < a.u) || (D < a.D);
    }
}node[maxn],S[maxn];
int head[maxn],q[maxn],d[maxn],nEdge;
int flag[maxn],dp[maxn],fa[maxn],ans[maxn],marts[maxn];
bool vis[maxn];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
    head[v] = nEdge;
}
int getroot(int x)
{
    int tail = 0,u,v,root,minv = inf;
    q[tail++] = x; fa[x] = -1;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        dp[u] = 1;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v != fa[u] && !flag[v])
            {
                q[tail++] = edges[k].v;
                fa[v] = u;
            }
        }
    }
    for(int i = tail - 1;i >= 0;--i)
    {
        u = q[i];
        int mx = 0;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v != fa[u] && !flag[v])
            {
                if(dp[v] > mx) mx = dp[v];
                dp[u] += dp[v];
            }
        }
        mx = max(mx,tail - dp[u]);
        if(mx < minv) minv = mx,root = u;
    }
    return root;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(flag,0,sizeof(flag));
    memset(vis,0,sizeof(vis));
    memset(d,0x3f,sizeof(d));
    memset(ans,0,sizeof(ans));
    nEdge = -1;
}
void precal(int n)
{
    queue<int>q;
    int u,v;
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&marts[i]);
        if(marts[i])
        {
            q.push(i);
            d[i] = 0;
            node[i] = Node(0,i);
        }
    }
    Node tmp;
    while(!q.empty())
    {
        u = q.front();q.pop();
        vis[u] = false;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            tmp = Node(node[u].D + edges[k].w,node[u].u);
            if(tmp < node[v])
            {
                node[v] = tmp;
                if(!vis[v]) { vis[v] = true;q.push(v);}
            }
        }
    }
}
void cal(int x,int pa,int prew,int sign)
{
    int tail = 0,u,v;
    q[tail++] = x;
    fa[x] = pa; d[x] = prew;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        for(int k = head[u] ;k != -1; k = edges[k].next)
        {
            v = edges[k].v;
            if(v != fa[u] && !flag[v])
            {
                fa[v] = u;
                d[v] = d[u] + edges[k].w;
                q[tail++] = v;
            }
        }
    }
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        S[i] = Node(node[u].D - d[u],node[u].u);
    }
    sort(S,S + tail);
    S[tail] = Node(inf,inf);
    int p;
    Node tmp;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        if(marts[u]) continue;
        tmp = Node(d[u],u);
        p = upper_bound(S,S+tail,tmp) - S;
        ans[u] += (tail - p)*sign;
    }
}
void solve(int u)
{
    int root = getroot(u);
    flag[root] = 1;
    for(int k = head[root];k != -1; k = edges[k].next)
        if(!flag[edges[k].v]) cal(edges[k].v,root,edges[k].w,-1);
    cal(root,-1,0,1);
    for(int k = head[root];k != -1; k = edges[k].next)
        if(!flag[edges[k].v]) solve(edges[k].v);
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        int u ,v, w;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        for(int i = 1;i <= n;++i)
            node[i] = Node(inf,0);
        precal(n);
        solve(1);
        int res = 0;
        for(int i = 1;i <= n;++i)
            res = max(res,ans[i]);
        printf("%d\n",res);
    }
    return 0;
}
