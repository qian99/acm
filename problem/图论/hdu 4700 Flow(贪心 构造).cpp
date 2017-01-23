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
const int maxn = 100 + 10;
struct Edge
{
    int u,v,w;
    Edge(int u = 0,int v = 0,int w = 0):u(u),v(v),w(w){}
    bool operator < (const Edge & a) const
    {
        return w > a.w;
    }
}edges[maxn*maxn];
int g[maxn][maxn],G[maxn][maxn],pa[maxn];
int A[maxn],B[maxn],cnt1,cnt2;
int Find(int x)
{
    return x == pa[x] ? x:pa[x] = Find(pa[x]);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                scanf("%d",&g[i][j]);
        for(int i = 1;i <= n;++i) pa[i] = i;
        int tot = 0;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(i != j) edges[tot++] = Edge(i,j,g[i][j]);
        sort(edges,edges + tot);
        memset(G,0,sizeof(G));
        bool flag = true;
        for(int i = 0;i < tot && flag;++i)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            if(Find(u) == Find(v)) continue;
            G[u][v] = G[v][u] =edges[i].w;
            u = Find(u); v = Find(v);
            cnt1 = 0;
            cnt2 = 0;
            for(int j = 1;j <= n;++j)
                if(Find(j) == u) A[cnt1++] = j;
            for(int j = 1;j <= n;++j)
                if(Find(j) == v) B[cnt2++] = j;
            for(int j = 0;j < cnt1;++j)
                for(int k = 0;k < cnt2;++k)
                {
                    if(g[A[j]][B[k]] != edges[i].w) flag =false;
                }
            pa[u] = v;
        }
        if(!flag) puts("NO");
        else
        {
            puts("YES");
            for(int i = 1;i <= n;++i)
            {
                for(int j = 1;j <= n;++j)
                {
                    if(j > 1) printf(" ");
                    if(i == j) printf("-1");
                    else printf("%d",G[i][j]);
                }
                puts("");
            }
        }
    }
    return 0;
}
