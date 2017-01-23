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
const int maxn=1000+10;
const int mod=1000000007;
ll dp[maxn];
int p[maxn];
//ÆæÊý->pi,Å¼Êý->next
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    ll ans=0;
    for(int i=1;i<=n;++i)
        scanf("%d",&p[i]);
    for(int i=1;i<=n;++i)
    {
        if(p[i]==i) dp[i]=2;
        else
        {
            for(int j=p[i];j<i;++j)
                dp[i]=(dp[i]+dp[j])%mod;
            dp[i]+=2;
        }
        ans=(ans+dp[i])%mod;
    }
    printf("%I64d\n",ans);
    return 0;
}