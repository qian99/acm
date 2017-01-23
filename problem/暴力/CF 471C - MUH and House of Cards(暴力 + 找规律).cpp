 /* 人一我百，人十我万！追逐青春的梦想，怀着自信的心，永不放弃！
        信kuangbin
           得WF名额！
       kuangbin带领我们
              挑战世界
*/
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
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll n,m;
    cin>>n;
    int ans = 0;
    for(ll i = 1;i <= 1000000;++i)
    {
        m = i*(i+1)*3/2 - i;
        if(n >= m && (n - m)%3 == 0)
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}
