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
const int mod = 1e9 + 7;
const int maxn = 1000 + 10;
int dp[200001];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll r,g,sum;
    scanf("%I64d%I64d",&r,&g);
    dp[0] = 1;
    int ans = 0,tmp;
    for(int i = 1;i <= 1000;++i)
    {
        for(int j = r;j >= i;--j)
        {
            if(dp[j - i] == 0) continue;
            dp[j] += dp[j - i];
            if(dp[j] >= mod) dp[j] -= mod;
        }
        tmp = -1;
        for(int j = 0;j <= r;++j)
        {
            if(dp[j] == 0) continue;
            sum = (ll)i*(i + 1)/2;
            if(sum - j <= g)
            {
                if(tmp == -1) tmp = dp[j];
                else
                {
                    tmp += dp[j];
                    if(tmp >= mod) tmp -= mod;
                }
            }
        }
        if(tmp != -1) ans = tmp;
    }
    printf("%d\n",ans);
    return 0;
}