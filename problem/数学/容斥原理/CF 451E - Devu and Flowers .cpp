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
const int mod=1000000000+7;
ll pow_mod(ll x,ll n)
{
    ll res=1;
    x%=mod;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
inline ll inv(ll x)
{
    return pow_mod(x,mod-2);
}
ll C(ll n,ll m)
{
    ll res=1,res2=1;
    for(int i=1;i<=m;++i)
    {
        res=res*((n-i+1)%mod)%mod;
        res2=res2*i%mod;
    }
    return res*inv(res2)%mod;
}
int cal(ll x)
{
    int cnt=0;
    while(x)
    {
        x=x&(x-1);
        cnt^=1;
    }
    return cnt;
}
ll a[55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    ll s;
    cin>>n>>s;
    for(int i=0;i<n;++i)
        cin>>a[i];
    ll ans=C(s+n-1,n-1),ss;
    for(int i=1;i<(1<<n);++i)
    {
        ss=s;
        for(int j=0;j<n;++j)
            if(i&(1<<j)) ss-=a[j]+1;
        if(ss<0) continue;
        else if(cal(i)) ans-=C(ss+n-1,n-1);
        else ans+=C(ss+n-1,n-1);
        ans%=mod;
    }
    ans=(ans%mod+mod)%mod;
    cout<<ans<<endl;
    return 0;
}