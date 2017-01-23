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
double P[maxn][55],dp[55][55];
int M,T,N;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&M,&T,&N))
    {
        if(M==0&&T==0&&N==0) break;
        double tmp,ans=1,ans2=1;
        for(int i=1;i<=T;++i)
        {
            memset(dp,0,sizeof(dp));
            dp[0][0]=1;
            for(int j=1;j<=M;++j)
            {
                scanf("%lf",&P[i][j]);
                tmp*=(1.0-P[i][j]);
            }
            for(int j=1;j<=M;++j)
                for(int k=0;k<=j;++k)
                {
                    if(k!=0) dp[j][k]=dp[j-1][k]*(1.0-P[i][j])+dp[j-1][k-1]*P[i][j];
                    else dp[j][k]=dp[j-1][k]*(1.0-P[i][j]);
                }
            tmp=0;
            for(int j=1;j<N;++j)
                tmp+=dp[M][j];
            ans2*=tmp;
            ans*=(1-dp[M][0]);
        }
        ans=ans-ans2;
        printf("%.3lf\n",ans);
    }
    return 0;
}
