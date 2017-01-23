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
const int maxn = 5000+10;
ll dp[maxn][maxn],sum[maxn],cost[maxn];
int n;
ll f(int L,int R)
{
    if(L < 1 && R > n) return 0;
    if(L < 1 || R > n) return Inf;
    if(sum[L] != sum[n] - sum[R-1]) return Inf;
    if(dp[L][R] != -1) return dp[L][R];
    ll & ans = dp[L][R];
    ans = Inf;
    ll tmp;
    int s = L,t = R;
    while(s >= 1 && t <= n)
    {
        if(sum[L] - sum[s - 1] == sum[t] - sum[R-1])
        {
            tmp = cost[L - s + 1] + cost[t - R + 1];
            tmp += f(s - 1, t + 1);
            ans = min(ans,tmp);
            if(s >= 2) s--;
            else t++;
        }
        else if(sum[L] - sum[s - 1] > sum[t] - sum[R-1])
            t++;
        else if(sum[L] - sum[s - 1] < sum[t] - sum[R-1])
            s--;
    }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        for(int i = 1;i <= n;++i)
            scanf("%I64d",&sum[i]);
        sum[0] = 0;
        for(int i = 1;i <= n;++i)
            sum[i] += sum[i-1];
        for(int i = 1;i <= n;++i)
            scanf("%I64d",&cost[i]);
        for(int i = 1;i <= n;++i)
            for(int j = i;j <= n;++j)
                dp[i][j] = -1;
        cost[0] = 0;
        ll ans = cost[n];
        for(int i = 1;i < n;++i)
        {
            ans = min(ans,f(i,i+1));
            if(i > 1) ans = min(ans,f(i-1,i+1));
        }
        int s = 1, t = n;
        while(s < t)
        {
            if(sum[s] == sum[n] - sum[t-1])
            {
                ans = min(ans,f(s,t)+cost[t-s-1]);
                s++;
            }
            else if(sum[s] < sum[n] - sum[t-1])
                s++;
            else t--;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

