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
const int maxn = 10000+10;
vector<int>G[maxn];
int dp[maxn];
void dfs(int u)
{
    dp[u] = 1;
    int vec[2];
    for(int i = 0;i < (int)G[u].size();++i)
    {
        vec[i] = G[u][i];
        dfs(vec[i]);
    }
    if(G[u].size())
    {
        if(G[u].size() == 1)
            dp[u] = dp[vec[0]];
        else
            dp[u] = min(max(dp[vec[0]]+1,dp[vec[1]]),max(dp[vec[0]],dp[vec[1]]+1));
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i = 0;i <= n;++i)
            G[i].clear();
        int v;
        for(int i = 2;i <= n;++i)
        {
            scanf("%d",&v);
            G[v].push_back(i);
        }
        dfs(1);
        printf("%d\n",dp[1]);
    }
    return 0;
}
