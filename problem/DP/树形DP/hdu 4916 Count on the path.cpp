#pragma comment(linker, "/STACK:1024000000,1024000000")
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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
pair<int,int>minv[maxn][4],rootval[4];
int dp[maxn],pa[maxn];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v, head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u, head[v]);
    head[v] = nEdge;
}
void dfs1(int u,int fa)
{
    minv[u][1] = minv[u][2] = minv[u][3] = make_pair(inf,inf);
    minv[u][0] = make_pair(u,u);
    for(int k = head[u]; k != -1; k=edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue;
        dfs1(v,u);
        pa[v]=u;
        minv[u][3] = make_pair(minv[v][0].first,v);
        sort(minv[u],minv[u] + 4);
    }
}
void dfs2(int u,int fa,int mval)
{
    int tmp=mval;
    if(minv[u][0].second == u)
        tmp = min(tmp,minv[u][1].first);
    else tmp = min(tmp,minv[u][0].first);
    dp[u] = tmp;
    for(int k = head[u];k != -1;k=edges[k].next)
    {
        int v = edges[k].v;
        if(v == fa) continue ;
        tmp = mval;
        if(minv[u][0].second != u && minv[u][0].second != v)
            tmp=min(tmp,minv[u][0].first);
        else if(minv[u][1].second != u && minv[u][1].second != v)
            tmp=min(tmp,minv[u][1].first);
        else tmp=min(tmp,minv[u][2].first);
        dfs2(v,u,tmp);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head ,0xff,sizeof(head));
        nEdge = -1;
        int u,v;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs1(1,-1);
        dp[1]=inf;
        rootval[0] =rootval[1] =rootval[2] =rootval[3] = make_pair(inf,inf);
        for(int k = head[1];k != -1;k=edges[k].next)
        {
            v = edges[k].v;
            dfs2(v,1,inf);
            rootval[3] = make_pair(minv[v][0].first,v);
            sort(rootval , rootval + 4);
            pa[v] = v;
        }
        int last = 0;
        while(m--)
        {
            scanf("%d%d",&u,&v);
            u ^= last;
            v ^= last;
            if(Find(u) == Find(v)) last = 1;
            else
            {
                last = min(dp[u] ,dp[v]);
                u = Find(u);
                v = Find(v);
                if(rootval[0].second != u && rootval[0].second != v)
                    last = min(last,rootval[0].first);
                else if(rootval[1].second != u && rootval[1].second != v)
                    last = min(last,rootval[1].first);
                else last = min(last,rootval[2].first);
            }
            printf("%d\n",last);
        }
    }
    return 0;
}
