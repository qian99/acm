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
class TaroCoins
{
public:
    ll dp[64][2];
    long long getNumber(long long N)
    {
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        if(!(N & 1))
        {
            dp[0][1] = 1;
        }
        for(ll i = 1;i <= 63 ;++i)
        {
            if((1LL<<i) & N)
            {
                dp[i][0] = dp[i-1][0] + dp[i-1][1];
                dp[i][1] = dp[i-1][1];
            }
            else
            {
                dp[i][0] = dp[i-1][0];
                dp[i][1] = dp[i-1][0] + dp[i-1][1];
            }
        }
        return dp[63][0];
    }
};
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    TaroCoins s;
    ll n;
    while(cin>>n)
    {
        cout<<s.getNumber(n)<<endl;
    }
    return 0;
}
