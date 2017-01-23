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
const int mod=1000000009;
const int A=691504013;
const int B=308495997;
ll pow_mod(ll x,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
ll inv(ll x)
{
    return (pow_mod(x,mod-2)+mod)%mod;
}
ll cal(ll q,ll n)
{
    if(q==1) return n%mod;
    ll tmp=pow_mod(q,n);
    tmp=(q*(tmp-1)%mod)*inv(q-1);
    return (tmp%mod+mod)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,k;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&k);
        ll sum=0,tmp,C=1;
        for(int i=0;i<=k;++i)
        {
            tmp=pow_mod(A,k-i)*pow_mod(B,i)%mod;
            tmp=cal(tmp,n);
            sum+=C*tmp*((i&1)?-1:1);
            sum%=mod;
            C=(C*(k-i)%mod)*inv(i+1)%mod;
        }
        sum=sum*pow_mod(inv(383008016),k)%mod;
        sum=(sum+mod)%mod;
        printf("%lld\n",sum);
    }
    return 0;
}
