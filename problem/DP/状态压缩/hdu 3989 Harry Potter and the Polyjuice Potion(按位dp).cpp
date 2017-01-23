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
const int maxn = 100000 + 10;
int val[1<<20],Hbit[1<<20],cnt[1<20];
ll dp[1<<20];
void Init()
{
    for(int i = 1;i < (1<<20);++i)
    {
        int j = 19;
        for(;j >= 0;j--)
            if(i & (1<<j)) break;
        Hbit[i] = j;
        j = i;
        cnt[i] = 0;
        while(j)
        {
            cnt[i]++;
            j = j&(j - 1);
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    Init();
    int n;
    while(~scanf("%d",&n))
    {
        if(n < 0) break;
        memset(val,0,sizeof(val));
        memset(dp,0,sizeof(dp));
        int x;
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&x);
            scanf("%d",&val[x]);
            dp[x] = val[x];
        }
        for(int i = 0;i < 20;++i)
        {
            for(int j = (1<<20) - 1;j >= 0;--j)
                if(j & (1<<i))
                    dp[j] += dp[j^(1<<i)];
        }
        ll ans = dp[0];
        for(int i = 0;i < (1<<20);++i)
            ans = max(ans,dp[i]);
        printf("%I64d\n",ans);
    }
    return 0;
}
