#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=100+10;
int num[maxn][maxn];
int dp[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    int n,m;
    while(t--)
    {
        scanf("%d%d",&m,&n);
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
               scanf("%d",&num[i][j]);
        }
        memset(dp,0,sizeof(dp));
        if(num[0][0]!=0)
        dp[0][0]=1;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                //dp[i][j]--;
                for(int k=0;k<=num[i][j]&&i+k<m;++k)
                {
                    for(int h=0;h<num[i][j]-k+1&&j+h<n;++h)
                    {
                        if(k==0&&h==0) continue;
                        dp[i+k][j+h]+=dp[i][j];
                        dp[i+k][j+h]%=10000;
                    }
                }
            }
        }
        printf("%d\n",dp[m-1][n-1]%10000);
    }
    return 0;
}
