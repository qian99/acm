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
const int maxn=200000+10;
const ll mxm=10000000000LL;
const int mod=100000007;
ll num[maxn],dp[maxn];
map<ll,int>mp;
ll f(int n)
{
    if(n<=1) return 1;
    if(dp[n]!=-1) return dp[n];
    ll &ans=dp[n]=0;
    for(int i=0;i<n;++i)
        ans=(ans+f(i)*f(n-i-1)%mod)%mod;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tot=0;
    ll tmp;
    mp.clear();
    for(ll x=2;x<maxn;++x)
    {
        if(x*x>mxm) break;
        tmp=x;
        for(int y=2;y<maxn;++y)
        {
            tmp*=x;
            if(tmp>mxm) break;
            if(mp.find(tmp)==mp.end())
            {
                num[tot++]=tmp;
                mp[tmp]=1;
            }
        }
    }
    sort(num,num+tot);
    memset(dp,0xff,sizeof(dp));
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        int L,R;
        L=lower_bound(num,num+tot,a)-num;
        R=upper_bound(num,num+tot,b)-num;
        printf("Case %d: ",++tcase);
        if(R-L==0) printf("0\n");
        else printf("%lld\n",f(R-L));
    }
    return 0;
}

