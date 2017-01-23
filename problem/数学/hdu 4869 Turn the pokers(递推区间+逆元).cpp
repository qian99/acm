#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
const int mod=1000000009;
const int maxn=100000+10;
ll p[maxn];
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
    return pow_mod(x,mod-2);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*i%mod;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int L=0,R=0,l,r,x;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&x);
            if(x>=L&&x<=R) l=((x&1)+(L&1))&1;
            else if(x<L) l=L-x;
            else l=x-R;

            if(R+x<=m) r=x+R;
            else if(L+x>=m) r=2*m-L-x;
            else
            {
                if((m&1)==(((x&1)+(L&1))&1)) r=m;
                else r=m-1;
            }
            L=l;R=r;
        }
        ll ans=0;
        for(int i=L;i<=R;i+=2)
            ans=(ans+p[m]*inv(p[i])%mod*inv(p[m-i])%mod)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
