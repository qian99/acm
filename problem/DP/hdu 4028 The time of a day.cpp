#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50;
map<ll,ll>dp[maxn];
ll gcd(ll a,ll b)
{
    ll c;
    while(b!=0)
    {
        c=b;
        b=a%b;
        a=c;
    }
    return a;
}
ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}
void getDp()
{
    dp[1][1]=1;
    for(int i=2;i<=40;++i)
    {
        dp[i]=dp[i-1];
        dp[i][i]++;
        map<ll,ll>::iterator it;
        for(it=dp[i-1].begin();it!=dp[i-1].end();++it)
        {
            ll tmp=lcm(it->first,i);
            dp[i][tmp]+=it->second;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getDp();
    int t,tcase=0;
    scanf("%d",&t);
    int n;
    ll m;
    while(t--)
    {
        tcase++;
        scanf("%d%I64d",&n,&m);
        map<ll,ll>::iterator it;
        ll ans=0;
        for(it=dp[n].begin();it!=dp[n].end();++it)
        {
            if(it->first>=m)
              ans+=it->second;
        }
        printf("Case #%d: %I64d\n",tcase,ans);
    }
    return 0;
}
