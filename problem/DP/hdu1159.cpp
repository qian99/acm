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
const int maxn=1000+10;
int dp[maxn][maxn];
char s1[maxn],s2[maxn];
int main()
{
    int m,n;
    while(~scanf("%s%s",s1+1,s2+1))
    {
        memset(dp,0,sizeof(dp));
        s1[0]=s2[0]='0';
        m=strlen(s1)-1;
        n=strlen(s2)-1;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(s1[i]==s2[j])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        printf("%d\n",dp[m][n]);
    }
    return 0;
}
