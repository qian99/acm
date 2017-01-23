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
const int maxn = 100000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0 ,int next = 0):v(v),next(next){}
}edges[maxn<<1];
struct Querys
{
    int type,x,y;
    Querys(int type = 0,int x = 0,int y = 0):type(type),x(x),y(y){}
}querys[maxn];
int head[maxn],qpos[maxn],qcnt,nEdge;
int L[maxn],R[maxn],degree[maxn],dfs_clock;
int pa[maxn],ans[maxn];
vector<int>G[maxn];
int Find(int x)
{
    return x == pa[x] ? x: pa[x] = Find(pa[x]);
}
void Uion(int x,int y)
{
    int a = Find(x);
    int b = Find(y);
    if(a != b)
        pa[b] = a;
}
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
void dfs(int u)
{
    L[u] = ++dfs_clock;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        dfs(edges[k].v);
//        G[u].push_back(make_pair(R[edges[k].v],edges[k].v));
    }
    R[u] = ++dfs_clock;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    qcnt = dfs_clock = 0;
    for(int i = 1;i <= m;++i)
    {
        scanf("%d",&querys[i].type);
        if(querys[i].type == 1)
        {
            scanf("%d%d",&querys[i].y,&querys[i].x);
            AddEdges(querys[i].x,querys[i].y);
            degree[querys[i].y]++;
        }
        else if(querys[i].type == 2)
        {
            scanf("%d",&querys[i].x);
            qpos[i] = ++qcnt;
        }
        else
        {
            scanf("%d%d",&querys[i].x,&querys[i].y);
            G[querys[i].y].push_back(i);
        }
    }
    for(int i = 1;i <= n;++i)
    {
        pa[i] = i;
        if(degree[i]) continue;
        dfs(i);
    }
    int u,v,p,id;
    for(int i = 1;i <= m;++i)
    {
        if(querys[i].type == 1)
            Uion(querys[i].x,querys[i].y);
        if(querys[i].type == 2)
        {
            p = qpos[i];
            for(int j = 0;j < (int)G[p].size();++j)
            {
                id = G[p][j];
                u = querys[id].x;
                v = querys[i].x;
                if(Find(u) == Find(v) && L[u] <= L[v] && R[u] >= R[v])
                    ans[id] = 1;
            }
        }
    }
    for(int i = 1;i <= m;++i)
        if(querys[i].type == 3)
            puts(ans[i]?"YES":"NO");
    return 0;
}