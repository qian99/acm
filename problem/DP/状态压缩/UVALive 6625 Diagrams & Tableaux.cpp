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
int L[10],n,m;
map<int,int>dp[2];
void dfs(int x,int y,int state,int val)
{
    if(y == L[x])
    {
        dp[x&1][state] += val;
        return ;
    }
    int limit = (state>>(y*3)) & 7;
    int pre = (y == 0)?1:((state>>(y*3-3))&7);
    for(int i = max(pre,limit + 1);i <= m;++i)
    {
        dfs(x,y + 1,((~(7<<(y*3)))&state) | (i<<(y*3)),val);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i = 1;i <= n;++i)
            scanf("%d",&L[i]);
        scanf("%d",&m);
        dp[0].clear();
        dp[1].clear();
        dp[0][0] = 1;
        int p = 0,ans = 0;
        for(int i = 1;i <= n;++i)
        {
            p = i & 1;
            dp[p].clear();
            for(map<int,int>:: iterator it = dp[p^1].begin();it != dp[p^1].end();it++)
            {
                dfs(i,0,it->first,it->second);
            }
        }
        for(map<int,int>:: iterator it = dp[n&1].begin();it != dp[n&1].end();it++)
            ans += it->second;
        printf("%d\n",ans);
    }
    return 0;
}

