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
const int maxn=100000+10;
ll a[maxn],cnt[maxn];
ll dp[maxn][2];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%I64d",&a[i]);
    sort(a+1,a+n+1);
    int N=0;
    a[0]=0;
    for(int i=1;i<=n;++i)
        if(a[i]==a[N]) cnt[N]++;
        else {a[++N]=a[i];cnt[N]=1;}
    dp[0][0]=dp[0][1]=0;
    for(int i=1;i<=N;++i)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
        if(a[i]==a[i-1]+1)
        {
            dp[i][1]=dp[i-1][0]+cnt[i]*a[i];
        }
        else dp[i][1]=max(dp[i-1][0],dp[i-1][1]) +cnt[i]*a[i];
    }
    ll ans=max(dp[N][0],dp[N][1]);
    printf("%I64d\n",ans);
    return 0;
}

