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
const int maxn = 1000 + 10;
int A[6][maxn],pos[maxn][6];
vector<int>G[maxn];
int dp[maxn];
void dfs(int u)
{
    if(dp[u] != -1) return ;
    dp[u] = 1;
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        dfs(v);
        dp[u] = max(dp[u],dp[v] + 1);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    memset(dp,0xff,sizeof(dp));
    for(int i = 1;i <= k;++i)
        for(int j = 1;j <= n;++j)
        {
            scanf("%d",&A[i][j]);
            pos[A[i][j]][i] = j;
        }
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++ j)
        {
            if(i == j) continue;
            bool flag = true;
            for(int x = 1; x <= k;++x)
                if(pos[i][x] > pos[j][x])
                    flag = false;
            if(flag)
                G[i].push_back(j);
        }
    int ans = 0;
    for(int i = 1;i <= n;++i)
    {
        if(dp[i] == -1)
            dfs(i);
        ans = max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}
