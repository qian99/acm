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
const int maxn = 1000000+10;
ll dp[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    dp[0] = 0;
    for(int i = 1;i < maxn;++i) dp[i] = dp[i-1]^i;
    int n;
    ll ans = 0,val;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        scanf("%I64d",&val);
        ans ^= val;
    }
    for(int i = 1;i <= n;++i)
    {
        int cnt = n - i;
        if(cnt & 1) ans ^= i;
    }
    for(int i = 2;i < n;++i)
    {
        int cnt = n - i + 1;
        if((cnt/i) & 1) ans ^= dp[i-1];
        if(cnt < i) ans ^= dp[cnt-1];
        else if(cnt%i) ans ^= dp[cnt%i-1];
    }
    printf("%I64d\n",ans);
    return 0;
}