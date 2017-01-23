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
ll num[maxn];
inline ll cal(ll n,ll k)
{
    ll res = n/k*k;
    if(res < n)
    {
        res += k;
    }
    return res;
}
inline ll check(int n)
{
    if(n < 2) return 0;
    ll d = num[n] - num[n-1];
    if(num[n-1] - num[n-2] != d) return 0;
    if(num[n-1]/(n-1) == num[n]/n) return d;
    return 0;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll x,k;
    int tcase = 0;
    while(~scanf("%I64d%I64d",&x,&k))
    {
        if(x == 0 && k == 0) break;
        printf("Case #%d: ",++tcase);
        ll ans = 0,d;
        int m = min(k,maxn-1LL);
        for(int i = 1;i <= m;++i)
        {
            x = num[i] = cal(x,i);
            d = check(i);
            if(d)
            {
                ans = x + (k-i)*d;
                break;
            }
            ans = x;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}