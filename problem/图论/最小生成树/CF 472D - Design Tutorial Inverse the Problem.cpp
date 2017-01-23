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
const int maxn = 2000 + 10;
struct Node
{
    int u,v,val;
    Node(int u = 0,int v = 0,int val = 0):u(u),v(v),val(val){}
    bool operator < (const Node & a) const
    {
        return val < a.val;
    }
}node[maxn*maxn];
struct Edge
{
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxn<<1];
int g[maxn][maxn];
ll d[maxn][maxn];
int head[maxn],nEdge;
int pa[maxn];
int Find(int x)
{
    return x == pa[x]?x:pa[x] = Find(pa[x]);
}
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
    head[v] = nEdge;
}
bool check(int n)
{
    for(int i = 1;i <= n;++i)
        if(g[i][i]) return false;
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            if(g[i][j] != g[j][i])
                return false;
    return true;
}
bool isSame(int n)
{
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            if(g[i][j] != d[i][j]) return false;
    return true;
}
void bfs(int s)
{
    memset(d[s],0xff,sizeof(d[s]));
    queue<int>q;
    q.push(s);
    d[s][s] = 0;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            int v = edges[k].v;
            if(d[s][v] == -1)
            {
                d[s][v] = d[s][u] + edges[k].w;
                q.push(v);
            }
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            scanf("%d",&g[i][j]);
    if(!check(n))
    {
        puts("NO");
        return 0;
    }
    int tot = 0;
    for(int i = 1;i <= n;++i)
        for(int j = i + 1;j <= n;++j)
            node[tot++] = Node(i,j,g[i][j]);
    sort(node,node + tot);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    for(int i = 1;i <= n;++i) pa[i] = i;
    for(int i = 0;i < tot;++i)
    {
        int x = Find(node[i].u);
        int y = Find(node[i].v);
        if(x != y && node[i].val > 0)
        {
            pa[y] = x;
            AddEdges(node[i].u,node[i].v,node[i].val);
        }
    }
    for(int i = 1;i <= n;++i)
        bfs(i);
    if(isSame(n))
        puts("YES");
    else
        puts("NO");
    return 0;
}