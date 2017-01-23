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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 50000+2;
const int mod = 10007;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
short dp[maxn][31][31],dp2[maxn][31][31];
char S[maxn],str1[33],str2[33];
int pa[maxn][18],d[maxn],val[33],val2[33],len;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    if(fa == -1)
    {
        pa[u][0] = d[u] = 0;
        memset(dp[u],0,sizeof(dp[u]));
        memset(dp2[u],0,sizeof(dp2[u]));
        for(int i = 0;i < len ;++i)
        {
            if(S[u] == str1[i]) dp[u][i][i]++;
            if(S[u] == str2[i]) dp2[u][i][i]++;
        }
    }
    for(int k = head[u];k != -1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v == fa) continue;
        memset(dp[v],0,sizeof(dp[v]));
        memset(dp2[v],0,sizeof(dp2[v]));
        for(int i = 0;i < len;++i)
        {
            if(S[v] == str1[i]) dp[v][i][i]++;
            if(S[v] == str2[i]) dp2[v][i][i]++;
            dp[v][i][i] += dp[u][i][i];
            if(dp[v][i][i] >= mod) dp[v][i][i] -= mod;
            dp2[v][i][i] += dp2[u][i][i];
            if(dp2[v][i][i] >= mod) dp2[v][i][i] -= mod;
            for(int j = i + 1;j < len;++j)
            {
                dp[v][i][j] += dp[u][i][j];
                dp2[v][i][j] += dp2[u][i][j];
                if(dp[v][i][j]>=mod) dp[v][i][j] -= mod;
                if(dp2[v][i][j]>=mod) dp2[v][i][j] -= mod;

                if(S[v] == str1[j])
                    dp[v][i][j] += dp[u][i][j-1];
                if(S[v] == str2[j])
                    dp2[v][i][j] += dp2[u][i][j-1];
                if(dp[v][i][j]>=mod) dp[v][i][j] -= mod;
                if(dp2[v][i][j]>=mod) dp2[v][i][j] -= mod;
            }
        }
        pa[v][0] = u;
        d[v] = d[u] + 1;
        dfs(v,u);
    }
}
void precal(int n)
{
    for(int i = 1;i <= 17;++i)
        for(int j = 1;j <= n;++j)
            pa[j][i] = pa[pa[j][i-1]][i-1];
}
int lca(int x,int y)
{
    if(x == y) return x;
    if(d[x] > d[y]) swap(x,y);
    for(int i =17;i >= 0;--i)
        if(d[pa[y][i]] > d[x]) y = pa[y][i];
    if(pa[y][0] == x) return x;
    if(d[y] > d[x]) y = pa[y][0];
    for(int i = 17;i >= 0;--i)
        if(pa[x][i] != pa[y][i])
        {
            x = pa[x][i];
            y = pa[y][i];
        }
    return pa[x][0];
}
void cal1(int u,int anc,int x)
{
    val[x] = (dp2[u][len-x-1][len-1]- dp2[anc][len-x-1][len-1])%mod;
    for(int i = 0;i < x;++i)
    {
        val[x] -= val[i]*dp2[anc][len-x-1][len-i-2];
        val[x] %= mod;
    }
}
void cal2(int u,int anc,int x)
{
    val2[x] = (dp[u][len-x-1][len-1] - dp[anc][len-x-1][len-1])%mod;
    for(int i = 0;i < x;++i)
    {
        val2[x] -= val2[i]*dp[anc][len-x-1][len-i-2];
        val2[x] %= mod;
    }
}
int solve(int u,int v)
{
    int anc = lca(u,v),ancf = pa[anc][0];
    int ans = 0;
    val[0] = (dp2[u][len-1][len-1] - dp2[ancf][len-1][len-1])%mod;
    for(int i = 1;i < len ;++i)
        cal1(u,ancf,i);
    val2[0] = (dp[v][len-1][len-1] - dp[anc][len-1][len-1])%mod;
    for(int i = 1;i < len ;++i)
        cal2(v,anc,i);
    ans += (val[len-1] + val2[len-1])%mod;
    for(int i = 0;i < len-1;++i)
    {
        ans += val[i]*val2[len-i-2];
        ans %= mod;
    }
    ans = (ans +mod)%mod;
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,q;
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        scanf("%d%d",&n,&q);
        int u,v;
        for(int i = 1; i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        scanf("%s%s",S+1,str1);
        len = strlen(str1);
        for(int i = 0;i < len;++i)
            str2[i] = str1[len-i-1];
        dfs(1,-1);
        precal(n);
        while(q--)
        {
            scanf("%d%d",&u,&v);
            printf("%d\n",solve(u,v));
        }
    }
    return 0;
}