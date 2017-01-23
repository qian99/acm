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
const int maxn = 450 + 10;
const int maxm = 900 + 10;
vector<int>G[maxn];
bool g[maxn][maxn];
int w[maxn],S[maxn],n,m,ans;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(g,0,sizeof(g));
        for(int i = 0;i <= n;++i)
            G[i].clear();
        for(int i = 1;i <= n;++i)
            scanf("%d",&w[i]);
        int u,v;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
            g[u][v] = g[v][u] = true;
        }
        ans = 0;
        int tot = 0,tmp;
        for(int i = 1;i <= n;++i)
        {
            tot = 0;
            for(int j = 0;j < (int)G[i].size();++j)
            {
                S[tot++] = G[i][j];
                ans = max(ans,w[i] + w[G[i][j]]);
            }
            for(int j = 0;j < tot;++j)
                for(int k = j + 1;k < tot;++k)
                {
                    if(!g[S[j]][S[k]]) continue;
                    tmp = w[i] + w[S[j]] + w[S[k]];
                    if(tmp > ans) ans = tmp;
                    for(int x = k + 1; x < tot;++x)
                    {
                        if(!g[S[j]][S[x]] || !g[S[k]][S[x]]) continue;
                        if(tmp + w[S[x]] > ans)
                            ans = tmp + w[S[x]];
                    }
                }
        }
        printf("%d\n",ans);
    }
    return 0;
}

