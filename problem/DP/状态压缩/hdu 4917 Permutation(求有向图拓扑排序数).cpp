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
const int maxn = 45;
const int mod = 1000000000+7;
vector<int>G[maxn];
int S[maxn],msk[maxn],id[maxn],N;
int degree[maxn],C[maxn][maxn],pa[maxn];
bool vis[maxn];
int dp[2][1<<21];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0] = 1;
    for(int i = 1;i < maxn ;++i)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j])%mod;
    }
}
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
void Uion(int x,int y)
{
    int a = Find(x);
    int b = Find(y);
    if(a != b) pa[b] = a;
}
void dfs(int u)
{
    vis[u] = true;
    for(int i = 0;i <(int)G[u].size();++i)
    {
        int v = G[u][i];
        if(vis[v])
        {
            msk[u] |= (msk[v]|(1<<id[v]));
            continue;
        }
        dfs(v);
        msk[u] |= (msk[v]|(1<<id[v]));
    }
}
int cal()
{
    for(int i = 0;i < 2;++i)
        for(int j = 0;j <(1<<N);++j)
            dp[i][j] = 0;
    dp[0][0] = 1;
    int p;
    for(int i = 0;i < N;++i)
    {
        p = i & 1;
        for(int j = 0;j < (1<<N);++j) dp[p^1][j] = 0;
        for(int j = 0;j < (1<<N);++j)
        {
            if(dp[p][j] == 0) continue;
            for(int k = 0;k < N;++k)
            {
                if((j&(1<<k))==0 && (j&msk[S[k]])==msk[S[k]])
                {
                    dp[p^1][j|(1<<k)] += dp[p][j];
                    if(dp[p^1][j|(1<<k)] >= mod) dp[p^1][j|(1<<k)] -= mod;
                }
            }
        }
    }
    return dp[N&1][(1<<N)-1];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int u,v;
        for(int i = 0;i < maxn;++i) G[i].clear();
        memset(degree,0,sizeof(degree));
        for(int i = 1;i <= n;++i) pa[i] = i;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            G[v].push_back(u);
            degree[u]++;
            Uion(u , v);
        }
        ll ans = 1,tmp;
        int tot = 0;
        memset(vis,0,sizeof(vis));
        memset(msk,0,sizeof(msk));
        for(int i = 1;i <= n;++i)
            if(pa[i] == i)
            {
                N = 0;
                for(int j = 1;j <= n;++j)
                {
                    if(Find(j) == i)
                    {
                        id[j] = N;
                        S[N++] = j;
                    }
                }
                for(int j = 0;j < N;++j)
                    if(!vis[S[j]]) dfs(S[j]);
                tmp = cal();
                ans = ans*tmp%mod*C[tot+N][N]%mod;
                tot += N;
            }
        for(int i = 1;i <= n;++i)
            if(degree[i] == 0)
            {
                N = 0;
                memset(msk,0,sizeof(msk));
                memset(vis,0,sizeof(vis));
                dfs(i);
                tmp = cal();
                ans = ans*tmp%mod*C[tot+N][N]%mod;
                tot += N;
            }
        printf("%I64d\n",ans);
    }
    return 0;
}
