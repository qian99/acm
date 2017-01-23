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
int dp[25][1<<10],val[25],msk[25],ok[1<<10],cost[25][1<<10],n;
int res[1<<10][1<<10][2];
inline int cal(int now,int add,int & next)
{
    next = 0;
    for(int k = 0;k < 10;++k)
    {
        int x = (now>>k&1) + (add>>k&1);
        if(x == 2)
        {
            next |= (1<<k);
            if(now>>k&1) now ^= (1<<k);
        }
        else if(x == 1)
        {
            if(!(now>>k&1))
                now ^= (1<<k);
        }
    }
    return now;
}
void Init()
{
    for(int i = 0;i < (1<<10);++i)
    {
        int x = i;
        ok[i] = 0;
        while(x)
        {
            ok[i]++;
            x = x&(x - 1);
        }
        ok[i] = (ok[i]&1)^1;
    }
    for(int i = 0;i < 20;++i)
    {
        for(int j = 0;j < (1<<10);++j)
        {
            cost[i][j] = 0;
            for(int k = 0;k < 10;++k)
                if(j & (1<<k))
                    cost[i][j] += 1<<i;
        }
    }
    for(int i = 0;i < (1<<10);++i)
        for(int j = 0;j < (1<<10);++j)
        {
            res[i][j][0] = cal(i,j,res[i][j][1]);
        }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    while(~scanf("%d",&n))
    {
        for(int i = 0;i < n;++i)
            scanf("%d",&val[i]);
        memset(msk,0,sizeof(msk));
        for(int i = 0;i < 20;++i)
        {
            for(int j = 0;j < n;++j)
                msk[i] |= (val[j]>>i&1)<<j;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][0] = 0;
        for(int i = 0;i < 20;++i)
        {
            int now,next,x,y;
            for(int j = 0;j < (1<<n);++j)
            {
                if(dp[i][j] == inf) continue;
                now = msk[i];next = 0;
                next = res[now][j][1];
                now =res[now][j][0];
//                now = cal(now,j,next);
                for(int k = 0;k < (1<<n);++k)
                {
                    if(k & now & next) continue;
//                    x = cal(now,k,y);
                    x = res[now][k][0];
                    y = res[now][k][1];
                    if(!ok[x]) continue;
                    dp[i+1][y|next] = min(dp[i+1][y|next],dp[i][j] + cost[i][k]);
                }
            }
        }
        int ans = inf;
        for(int i = 0;i < (1<<n);++i)
        {
            if(ok[i])
                ans = min(ans,dp[20][i]);
        }
        if(ans == inf)
            puts("impossible");
        else
            printf("%d\n",ans);
    }
    return 0;
}
