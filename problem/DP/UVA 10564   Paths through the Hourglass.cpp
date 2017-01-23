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
const int maxn=500+10;
ll dp[50][25][maxn];
int num[50][25];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,s;
    while(~scanf("%d%d",&n,&s))
    {
        if(n==0&&s==0) break;
        for(int i=1;i<=n;++i)
         for(int j=1;j<=n-i+1;++j)
           scanf("%d",&num[i][j]);
        for(int i=n+1;i<2*n;++i)
          for(int j=1;j<=i-n+1;++j)
            scanf("%d",&num[i][j]);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i) dp[2*n-1][i][num[2*n-1][i]]=1;
        for(int i=2*n-2;i>=n;--i)
            for(int j=1;j<=i-n+1;++j)
                for(int k=s;k>=num[i][j];--k)
                {
                    if(dp[i+1][j][k-num[i][j]])
                      dp[i][j][k]+=dp[i+1][j][k-num[i][j]];
                    if(dp[i+1][j+1][k-num[i][j]])
                      dp[i][j][k]+=dp[i+1][j+1][k-num[i][j]];
                }
        for(int i=n-1;i>=1;--i)
          for(int j=1;j<=n-i+1;++j)
             for(int k=s;k>=num[i][j];--k)
             {
                 if(j-1>0&&dp[i+1][j-1][k-num[i][j]])
                    dp[i][j][k]+=dp[i+1][j-1][k-num[i][j]];
                 if(j<=n-i&&dp[i+1][j][k-num[i][j]])
                    dp[i][j][k]+=dp[i+1][j][k-num[i][j]];
             }
        int st=inf;
        ll ans=0;
        for(int i=1;i<=n;++i)
        {
            if(dp[1][i][s])
            {
                ans+=dp[1][i][s];
                st=min(st,i);
            }
        }
        if(ans==0) printf("%lld\n\n",ans);
        else
        {
            printf("%lld\n",ans);
            printf("%d ",st-1);
            int sum=s;
            for(int i=1;i<n;++i)
            {
                if(st-1>0&&dp[i+1][st-1][sum-num[i][st]])
                {
                    sum-=num[i][st];
                    st=st-1;
                    printf("L");
                    continue;
                }
                if(st<n-i+1&&dp[i+1][st][sum-num[i][st]])
                {
                    sum-=num[i][st];
                    printf("R");
                }
            }
            for(int i=n;i<2*n-1;++i)
            {
                if(dp[i+1][st][sum-num[i][st]])
                {
                    sum-=num[i][st];
                    printf("L");
                    continue;
                }
                if(dp[i+1][st+1][sum-num[i][st]])
                {
                    sum-=num[i][st];
                    st++;
                    printf("R");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
