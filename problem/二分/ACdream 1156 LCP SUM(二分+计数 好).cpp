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
ll cal(int x,ll n)
{
    ll L=1,R=n+1;
    if(L*10+x+1>n) return 0;
    while(R-L>1)
    {
        ll m=(L+R)>>1;
        if(m*10+x+1<=n) L=m;
        else R=m;
    }
    ll res=(1+L)*L/2;
    return res;
}
ll solve(ll n)
{
    ll res=0;
    for(int i=0;i<9;++i)
    {
        res+=cal(i,n);
    }
    if(n>10) res+=solve(n/10);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    while(~scanf("%lld",&n))
    {
        printf("%lld\n",solve(n));
    }
    return 0;
}
