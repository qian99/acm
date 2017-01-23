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
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll a,b;
    cin>>a>>b;
    ll ans = 0;
    for(int i = 1;i <= b - 1;++i)
    {
        ans += (((a + 1)*a/2)%mod*b%mod + a)*i%mod;
        ans %= mod;
    }
    cout<<ans<<endl;
    return 0;
}