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
const int maxn=100+10;
char a[maxn],b[maxn];
int dp[maxn][maxn],ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s%s",a,b))
    {
        int n=strlen(a);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;++i)
            dp[i][i]=1;
        for(int k=2;k<=n;++k)
            for(int i=0;i<=n-k;++i)
            {
                dp[i][i+k-1]=dp[i+1][i+k-1]+1;
                for(int j=i+1;j<=i+k-1;++j)
                    if(b[i]==b[j])
                        dp[i][i+k-1]=min(dp[i][i+k-1],dp[i+1][j]+dp[j+1][i+k-1]);
            }
        for(int i=0;i<n;++i)
            ans[i]=dp[0][i];
        ans[0]=(a[0]==b[0])?0:1;
        for(int i=1;i<n;++i)
        {
            if(a[i]==b[i])
                ans[i]=ans[i-1];
            else
            {
                for(int j=0;j<i;++j)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
            }
        }
        printf("%d\n",ans[n-1]);
    }
    return 0;
}
