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
const int maxn=10000000+5;
const int mod=1000000007;
int pa[maxn];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n+1;++i) pa[i]=i;
        int N=n,x,y;
        while(m--)
        {
            scanf("%d%d",&x,&y);
            y++;
            x=Find(x);y=Find(y);
            if(x!=y)
            {
                N--;
                pa[x]=y;
            }
        }
        ll ans=pow_mod(26,N);
        printf("%I64d\n",ans);
    }
    return 0;
}
