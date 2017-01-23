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
    int v,w,next;
    Edge(int v = 0,int w = 0,int next = 0):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],repair[maxn],nEdge;
int flag[maxn],q[maxn],pa[maxn],fail;
int ans[maxn],tot;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge] = Edge(v,w,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,w,head[v]);
    head[v] = nEdge;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    int u,v,w;
    memset(head,0xff,sizeof(head));
    nEdge = - 1;
    for(int i = 1;i < n;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdges(u,v,w);
    }
    fail = 0;
    q[fail++] = 1;
    for(int h = 0; h < fail; ++h)
    {
        int u = q[h];
        for(int k = head[u] ;k != -1; k = edges[k].next)
        {
            int v = edges[k].v;
            if(v == pa[u]) continue;
            pa[v] = u;
            if(edges[k].w == 2) repair[v] = 1;
            q[fail++] = v;
        }
    }
    tot = 0;
    for(int i = fail - 1;i >= 0;--i)
    {
        int u = q[i];
        if(flag[u]) continue;
        if(repair[u])
        {
            ans[tot++] = u;
            while(u && !flag[u])
            {
                flag[u] = 1;
                u = pa[u];
            }
        }
    }
    printf("%d\n",tot);
    for(int i = 0; i < tot;++i)
    {
        if(i > 0) printf(" ");
        printf("%d",ans[i]);
    }
    printf("\n");
    return 0;
}