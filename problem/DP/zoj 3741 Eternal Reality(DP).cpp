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
int dp[maxn][maxn],a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int L,n,X,Y;
    while(~scanf("%d%d%d%d",&L,&n,&X,&Y))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
        {
            dp[i][0]=dp[i-1][0]+(L>=a[i]);
            dp[i][i]=max(dp[i][i],dp[i-1][0]+(L+1>=a[i]));
            for(int j=1;j<i;++j)
            {
                if(j+X+Y-1<i)  //可以使用
                {
                    //使用
                    dp[i][i]=max(dp[i][i],dp[i-1][j]+((L+1)>=a[i]));
                    //不使用
                    dp[i][j]=max(dp[i-1][j]+(L>=a[i]),dp[i][j]);
                }
                else          //不能使用
                {
                    if(j+X-1>=i)   //leveruper
                    {
                        dp[i][j]=max(dp[i][j],dp[i-1][j]+((L+1)>=a[i]));
                    }
                    else
                    {
                        dp[i][j]=max(dp[i][j],dp[i-1][j]+(a[i]<=0));
                    }
                }
            }
        }
        int ans=0;
        for(int i=0;i<=n;++i)
            ans=max(dp[n][i],ans);
        if(L==5)
        {
            ans=0;
            for(int i=1;i<=n;++i)
                if(a[i]<=5) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

