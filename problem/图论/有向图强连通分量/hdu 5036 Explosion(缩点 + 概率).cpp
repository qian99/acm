//一个点上用炸弹，当且仅当能到达它的其他点没有用炸弹
//即在点u使用炸弹的期望等于1 × (1/cnt[u]) ，cnt[u]为能够到达u的点的个数(包括u)
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
vector<int>G[maxn],g[maxn];
int pre[maxn],degree[maxn],sccno[maxn],cnt[maxn];
int dfs_clock,scc_cnt,n;
bitset<maxn>bt[maxn];
stack<int>S;
void Init()
{
    memset(pre,0,sizeof(pre));
    memset(degree,0,sizeof(degree));
    memset(sccno,0,sizeof(sccno));
    dfs_clock = scc_cnt = 0;
    for(int i = 0;i <= n;++i)
    {
        bt[i].reset();
        G[i].clear();
        g[i].clear();
    }
}
int tarjan(int u)
{
    int lowu = pre[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        if(!pre[v])
        {
            int lowv = tarjan(v);
            lowu = min(lowu,lowv);
        }
        else if(!sccno[v])
            lowu = min(lowu,pre[v]);
    }
    if(lowu == pre[u])
    {
        ++scc_cnt;
        for(;;)
        {
            int x = S.top();S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
    return lowu;
}
void solve()
{
    memset(cnt,0,sizeof(cnt));
    for(int u = 0;u < n;++u)
    {
        bt[sccno[u]][u] = 1;
        for(int i = 0;i < (int)G[u].size();++i)
        {
            int v = G[u][i];
            if(sccno[u] != sccno[v])
            {
                g[sccno[u]].push_back(sccno[v]);
                degree[sccno[v]]++;
            }
        }
    }
    queue<int>q;
    for(int i = 1;i <= scc_cnt;++i)
        if(degree[i] == 0) q.push(i);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int i = 0;i < (int)g[u].size();++i)
        {
            int v = g[u][i];
            bt[v] |= bt[u];
            degree[v]--;
            if(degree[v] == 0)
                q.push(v);
        }
    }
    for(int i = 1;i <= scc_cnt;++i)
        for(int j = 0;j < n;++j)
            if(bt[i][j]) cnt[i]++;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        Init();
        int u,k;
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&u);
                G[i].push_back(u - 1);
            }
        }
        for(int i = 0;i < n;++i)
            if(!pre[i]) tarjan(i);
        solve();
        double ans = 0;
        for(int i = 0;i < n;++i)
            ans += 1.0/cnt[sccno[i]];
        printf("Case #%d: %.5lf\n",++tcase,ans);
    }
    return 0;
}
