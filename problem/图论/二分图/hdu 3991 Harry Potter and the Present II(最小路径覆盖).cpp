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
const int maxm = 500000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxm];
ll dis[111][111];
int head[maxn],nEdge,n,m,q;
pair<int,int>request[maxn];
int vis[maxn],flag[maxn],links[maxn],T;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
void floyd(int n)
{
    for(int k = 0;k < n;++k)
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
}
bool dfs(int u)
{
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(vis[v] != T)
        {
            vis[v] = T;
            if(links[v] == -1 || dfs(links[v]))
            {
                links[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    memset(vis,0,sizeof(vis));
    memset(links,0xff,sizeof(links));
    T = 0;
    int res = 0;
    for(int i = 1;i <= q;++i)
    {
        T++;
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&q);
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                dis[i][j] = (i == j)?0:Inf;
        int u,v,w;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            dis[u][v] = dis[v][u] = min(dis[u][v],(ll)w);
        }
        floyd(n);
        for(int i = 1;i <= q;++i)
            scanf("%d%d",&request[i].first,&request[i].second);
        memset(flag,0,sizeof(flag));
        for(int i = 1;i <= q;++i)
        {
            if(flag[i]) continue;
            for(int j = i + 1;j <= q;++j)
            {
                if(dis[request[i].first][request[j].first] == 0 && request[i].second == request[j].second)
                    flag[j] = true;
            }
        }
        int tot = 0;
        for(int i = 1;i <= q;++i)
            if(!flag[i]) request[++tot] = request[i];
        q = tot;
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        for(int i = 1;i <= q;++i)
            for(int j = 1;j <= q;++j)
            {
                if(i == j) continue;
                if(request[i].second + dis[request[i].first][request[j].first] <= request[j].second)
                    AddEdges(i,j + q);
            }
        int ans = q;
        ans -= hungary();
        printf("Case %d: %d\n",++tcase,ans - 1);
    }
    return 0;
}
