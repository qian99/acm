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
vector<int>G[maxn];
vector<int>block[maxn][2],ans[2];
int color[maxn],id[maxn],flag[maxn],cnt;
int dp[maxn][maxn][maxn],path[maxn][maxn][maxn];
bool bipartite(int u)
{
    id[u] = cnt;
    for(int i=0;i< (int)G[u].size();++i)
    {
        int v=G[u][i];
        if(color[u]==color[v]) return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v)) return false;
        }
    }
    return true;
}
void printpath(int x,int y)
{
    ans[0].clear();
    ans[1].clear();
    for(int i = cnt;i >= 1;--i)
    {
        int p = path[i][x][y];
        for(int j = 0;j < (int)block[i][p].size();++j)
            ans[0].push_back(block[i][p][j]);
        for(int j = 0;j < (int)block[i][p^1].size();++j)
            ans[1].push_back(block[i][p^1][j]);
        x -= block[i][p].size();
        y -= block[i][p^1].size();
    }
    printf("%d",ans[0].size());
    for(int i = 0;i < (int)ans[0].size();++i)
        printf(" %d",ans[0][i]);
    puts("");
    printf("%d",ans[1].size());
    for(int i = 0;i < (int)ans[1].size();++i)
        printf(" %d",ans[1][i]);
    puts("");
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        if(tcase > 0) puts("");
        tcase++;
        int n ;
        scanf("%d",&n);
        for(int i = 0;i < maxn;++i)
        {
            G[i].clear();
            block[i][0].clear();
            block[i][1].clear();
        }
        for(int i = 1;i <= n;++i)
        {
            memset(flag,0,sizeof(flag));
            int u;
            while(true)
            {
                scanf("%d",&u);
                if(u == 0) break;
                flag[u] = true;
            }
            flag[i] = true;
            for(int j = 1; j <= n;++j)
            {
                if(!flag[j])
                {
                    G[j].push_back(i);
                    G[i].push_back(j);
                }
            }
        }
        memset(id,0,sizeof(id));
        memset(color,0,sizeof(color));
        cnt = 0;
        bool canit = true;
        for(int i = 1;i <= n;++i)
        {
            if(!id[i])
            {
                ++cnt;
                color[i] = 1;
                if(!bipartite(i))
                    canit = false;
            }
        }
        if(!canit)
        {
            puts("No solution");
            continue;
        }
        for(int i = 1;i <= n;++i)
        {
            block[id[i]][color[i] - 1].push_back(i);
        }
        memset(dp,0,sizeof(dp));
        dp[0][0][0] = 1;
        int a,b;
        for(int i = 0;i < cnt;++i)
            for(int j = 0;j <= n;++j)
                for(int k = 0;k <= n;++k)
                {
                    if(!dp[i][j][k]) continue;
                    a = block[i+1][0].size();
                    b = block[i+1][1].size();
                    dp[i+1][j+a][k+b] = 1;
                    path[i+1][j+a][k+b] = 0;
                    dp[i+1][j+b][k+a] = 1;
                    path[i+1][j+b][k+a] = 1;
                }
        bool isfind = false;
        for(int d = 0;d <= n && !isfind ;++d)
        {
            for(int i = 0;i + d<= n;++i)
                if(dp[cnt][i][i+d])
                {
                    isfind = true;
                    printpath(i,i+d);
                    break;
                }
                else if(dp[cnt][i+d][i])
                {
                    isfind = true;
                    printpath(i+d,i);
                    break;
                }
        }
    }
    return 0;
}
