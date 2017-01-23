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
int dp[1<<20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,k,L;
        scanf("%d%d%d",&n,&k,&L);
        ll ex=1;
        if(L>k) ex+=L-k;
        L=min(L,k);
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        int msk=(1<<k)-1;
        for(int i=0;i<n;++i)
        {
            for(int j=(1<<k)-1;j>=0;--j)
            {
                int val=dp[j],state;
                if(dp[j]==0) continue;
                dp[j]=0;
                for(int x=1;x<=L;++x)
                {
                    state=j|((j<<x)&msk)|(1<<(x-1));
                    dp[state]+=val;
                    if(dp[state]>=mod) dp[state]-=mod;
                }
                dp[j]+=ex*val%mod;
                if(dp[j]>=mod) dp[j]-=mod;
            }
        }
        int ans=0;
        for(int i=0;i<(1<<k);++i)
            if(i&(1<<(k-1)))
            {
                ans+=dp[i];
                if(ans>=mod) ans-=mod;
            }
        printf("%d\n",ans);
    }
    return 0;
}

