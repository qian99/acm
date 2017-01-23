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
const int maxn=200+10;
char str[maxn];
int dp[maxn][maxn],n;
int check(int s,int t,int k)
{
    if((t-s+1)%k!=0) return 0;
    for(int i=s+k;i<=t;i+=k)
    {
        for(int j=0;j<k;++j)
          if(str[s+j]!=str[i+j]) return 0;
    }
    return (t-s+1)/k;
}
inline int getnum(int x)
{
    if(x>=0&&x<=9) return 1;
    if(x>=10&&x<=99) return 2;
    return 3;
}
void solve()
{
    for(int i=0;i<n;++i)
     dp[i][i]=1;
    int tmp;
    for(int k=2;k<=n;++k)
    {
        for(int i=0;i<=n-k;++i)
        {
            dp[i][i+k-1]=inf;
            for(int j=i;j<i+k-1;++j)
              dp[i][i+k-1]=min(dp[i][i+k-1],dp[i][j]+dp[j+1][i+k-1]);
            for(int z=1;z<=k/2;++z)
            {
                tmp=check(i,i+k-1,z);
                if(tmp)
                  dp[i][i+k-1]=min(dp[i][i+k-1],dp[i][i+z-1]+2+getnum(tmp));
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        n=strlen(str);
        solve();
        printf("%d\n",dp[0][n-1]);
    }
    return 0;
}
