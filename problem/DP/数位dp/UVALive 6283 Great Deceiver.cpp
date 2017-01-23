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
const int maxn = 55;
int num[maxn],K;
ll dp[maxn];
ll f(int pos,int limit)
{
    if(pos == -1) return 1;
    if(dp[pos] != -1 && !limit) return dp[pos];
    ll ans = 0;
    int last = limit ? num[pos] : K - 1;
    if(pos & 1)
        ans += f(pos - 1,limit && 0 == last);
    else
    {
        for(int i = 0;i <= last;++i)
            ans += f(pos - 1,limit && i == last);
    }
    if(!limit) dp[pos] = ans;
    return ans;
}
ll cal(ll n)
{
    memset(dp,0xff,sizeof(dp));
    int len = 0;
    while(n)
    {
        num[len++] = n % K;
        n /= K;
    }
    return f(len - 1,1);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll n;
    while(~scanf("%lld%d",&n,&K))
    {
        memset(dp,0xff,sizeof(dp));
        printf("%lld\n",cal(n));
    }
    return 0;
}
