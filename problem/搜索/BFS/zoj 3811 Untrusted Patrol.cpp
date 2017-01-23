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
const int maxm = 200000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
int vis[maxn],rank[maxn],n,m,K,L;
int haves[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
bool bfs()
{
    memset(vis,0,sizeof(vis));
    queue<int>q;
    vis[rank[1]] = 1;
    q.push(rank[1]);
    int findnow = 2;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int k = head[u] ;k != -1;k = edges[k].next)
        {
            int v = edges[k].v;
            if(!vis[v])
            {
                vis[v] = findnow;
                if(!haves[v]) q.push(v);
                else if(v == rank[findnow])
                {
                    while(findnow <= L && vis[rank[findnow]])
                    {
                        q.push(rank[findnow]);
                        findnow++;
                    }
                }
            }
        }
    }
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return false;
    if(findnow > L) return true;
    return false;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&K);
        memset(head,0xff,sizeof(head));
        memset(haves,0,sizeof(haves));
        nEdge = -1;
        int u,v;
        for(int i = 1;i <= K;++i)
        {
            scanf("%d",&u);
            haves[u] = 1;
        }
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        scanf("%d",&L);
        for(int i = 1;i <= L;++i)
            scanf("%d",&rank[i]);
        if(L < K)
        {
            puts("No");
            continue;
        }
        bool res = bfs();
        if(res) puts("Yes");
        else puts("No");
    }
    return 0;
}