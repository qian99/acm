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
#define mpair(a,b,c) make_pair(make_pair(a,b),c)
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
const int maxm = 3000 + 10;
struct Edge
{
    int v,l,r,next;
    Edge(int v = 0,int l = 0,int r = 0,int next = 0):v(v),l(l),r(r),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge,n,m;
int a[maxm],b[maxm];
int vis[maxn],cnt;
void AddEdges(int u,int v,int l,int r)
{
    edges[++nEdge] = Edge(v,l,r,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,l,r,head[v]);
    head[v] = nEdge;
}
bool dfs(int u,int L,int R)
{
    if(u == n) return true;
    vis[u] = cnt;
    for(int k = head[u] ;k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(vis[v] == cnt) continue;
        if(L < edges[k].l || R > edges[k].r) continue;
        if(dfs(v,L,R)) return true;
    }
    return false;
}
int solve()
{
    int ans = 0;
    cnt = 0;
    memset(vis,0,sizeof(vis));
    sort(a,a + m);
    sort(b,b + m);
    int L,R,mid;
    for(int i = 0;i < m;++i)
    {
        L = a[i];
        R = b[m-1];
        while(L <= R)
        {
            mid = (L + R)>>1;
            ++cnt;
            if(dfs(1,a[i],mid))
            {
                ans = max(ans,mid - a[i] + 1);
                L = mid + 1;
            }
            else
                R = mid - 1;
        }
    }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    int u,v,l,r;
    for(int i = 0;i < m;++i)
    {
        scanf("%d%d%d%d",&u,&v,&l,&r);
        AddEdges(u,v,l,r);
        a[i] = l;
        b[i] = r;
    }
    int ans = solve();
    if(ans == 0) printf("Nice work, Dima!\n");
    else printf("%d\n",ans);
    return 0;
}
