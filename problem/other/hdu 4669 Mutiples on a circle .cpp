#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50000+10;
const int maxmod=200+10;
int digit[maxn],num[maxn],dp[maxn][maxmod];
int e[maxn*3];
inline int getdigit(int n)
{
    if(!n) return 1;
    int ret=0;
    while(n!=0) {n/=10;ret++;}
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,mod;
    while(~scanf("%d%d",&n,&mod))
    {
        e[0]=1;
        for(int i=1;i<=n*3;++i)
          e[i]=(e[i-1]*10)%mod;
        memset(dp,0,sizeof(int)*n*maxmod);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&num[i]);
            digit[i]=getdigit(num[i]);
        }
        int ans=0,length=0,s=0;
        num[n]=num[0];
        digit[n]=digit[0];
        for(int i=n;i>0;--i)
        {
            s=(s+e[length]*num[i])%mod;
            length+=digit[i];
            dp[0][s]++;
        }
        ans+=dp[0][0];
        for(int i=1;i<n;++i)
        {
            for(int j=0;j<mod;++j)
               if(dp[i-1][j]) dp[i][(j*e[digit[i]]+num[i])%mod]+=dp[i-1][j];
            s=(s*e[digit[i]]+num[i])%mod;
            dp[i][s]--;
            dp[i][num[i]%mod]++;
            s=((s-num[i]*e[length])%mod+mod)%mod;
            ans+=dp[i][0];
        }
        printf("%d\n",ans);
    }
    return 0;
}
