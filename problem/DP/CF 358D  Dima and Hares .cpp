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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=3000+10;
int a[maxn],b[maxn],c[maxn];
int dp[maxn][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
          scanf("%d",&a[i]);
        for(int i=1;i<=n;++i)
          scanf("%d",&b[i]);
        for(int i=1;i<=n;++i)
          scanf("%d",&c[i]);
        memset(dp,0,sizeof(dp));
        if(n==1)
        {
            printf("%d\n",a[1]);
            continue;
        }
        dp[2][0]=b[1];dp[2][1]=a[1];
        for(int i=3;i<=n;++i)
        {
            dp[i][0]=max(dp[i-1][0]+b[i-1],dp[i-1][1]+c[i-1]);
            dp[i][1]=max(dp[i-1][0]+a[i-1],dp[i-1][1]+b[i-1]);
        }
        printf("%d\n",max(dp[n][0]+a[n],dp[n][1]+b[n]));
    }
    return 0;
}
