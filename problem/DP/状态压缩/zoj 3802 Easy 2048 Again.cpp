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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
map<ll,ll>dp[2];
map<ll,ll>:: iterator it;
inline void Update(int p,ll s,ll w)
{
    if(dp[p].find(s) != dp[p].end())
        dp[p][s] = max(dp[p][s],w);
    else dp[p][s] = w;
}
void cal(ll val,int p)
{
    dp[p].clear();
    ll state,w,v;
    for(it = dp[p^1].begin();it != dp[p^1].end();it++)
    {
        state = it -> first;
        w = it -> second;
        v = val;
        Update(p,state,w);
        w += v;
        if(state & (v-1))
        {
            Update(p,v,w);
        }
        else
        {
            while(state & v)
            {
                state ^= v;
                v <<= 1;
                w += v;
            }
            state |= v;
            Update(p,state,w);
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        dp[0].clear();
        dp[1].clear();
        dp[0][0] = 0;
        int val;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&val);
            cal(val,i&1);
        }
        ll ans = 0;
        for(it = dp[n&1].begin();it != dp[n&1].end();it++)
            ans = max(ans,it->second);
        printf("%lld\n",ans);
    }
    return 0;
}
