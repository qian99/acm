#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int mod=1000000007;
const int maxn=2000+10;
ll C[maxn][maxn];
void init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=C[i-1][j-1]+C[i-1][j];
            if(C[i][j]>=mod-1) C[i][j]-=(mod-1);
        }
    }
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
    init();
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        if(n==1)
        {
            printf("%d\n",m);
            continue;
        }
        ll ans=1;
        for(int i=1;i<=m;++i)
        {
            ans=ans*pow_mod(i,C[n+m-i-2][n-2]*n%(mod-1))%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
