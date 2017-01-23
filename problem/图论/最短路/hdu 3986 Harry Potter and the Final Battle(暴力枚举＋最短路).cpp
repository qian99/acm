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
const int maxn = 1000 + 10;
const int maxm = 50000 + 10;
struct Edge
{
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],p[maxn],n,m,nEdge;
bool inq[maxn],ban[maxm<<1];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
    head[v] = nEdge;
}
void spfa(int flag)
{
    queue<int>q;
    for(int i = 0;i <= n;++i)
    {
        d[i] = inf;
        inq[i] = false;
    }
    q.push(1);
    d[1] = 0;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        inq[u] = false;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            if(ban[k]) continue;
            int v = edges[k].v;
            if(d[v] > d[u] + edges[k].w)
            {
                d[v] = d[u] + edges[k].w;
                if(flag) p[v] = k;
                if(!inq[v]) {inq[v] = true;q.push(v);}
            }
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u,v,w;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        for(int i = 0;i <= nEdge; ++i)
            ban[i] = false;
        memset(p,0xff,sizeof(p));
        spfa(1);
        if(d[n] == inf)
        {
            puts("-1");
            continue;
        }
        int ans = -1;
        u = n;
        while(u != 1)
        {
            ban[p[u]] = true;
            ban[p[u]^1] = true;
            spfa(0);
            ans = max(ans,d[n]);
            ban[p[u]] = false;
            ban[p[u]^1] = false;
            u = edges[p[u]^1].v;
        }
        if(ans == inf) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}
