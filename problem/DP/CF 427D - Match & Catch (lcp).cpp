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
typedef unsigned long long Ull;
const int maxn=5000+10;
char str1[maxn],str2[maxn];
int n,m,dp[3][maxn][maxn],mx1[maxn],mx2[maxn];
int solve()
{
    for(int i=n-1;i>=0;--i)
    {
        mx1[i]=0;
        for(int j=n-1;j>=0;--j)
        {
            if(str1[i]==str1[j]) dp[0][i][j]=dp[0][i+1][j+1]+1;
            else dp[0][i][j]=0;
            if(i!=j) mx1[i]=max(mx1[i],dp[0][i][j]);
        }
    }
    for(int i=m-1;i>=0;--i)
    {
        mx2[i]=0;
        for(int j=m-1;j>=0;--j)
        {
            if(str2[i]==str2[j]) dp[1][i][j]=dp[1][i+1][j+1]+1;
            else dp[1][i][j]=0;
            if(i!=j) mx2[i]=max(mx2[i],dp[1][i][j]);
        }
    }
    int ans=inf,len;
    for(int i=n-1;i>=0;--i)
    {
        for(int j=m-1;j>=0;--j)
        {
            if(str1[i]==str2[j]) dp[2][i][j]=dp[2][i+1][j+1]+1;
            else dp[2][i][j]=0;
            len=dp[2][i][j];
            if(len>mx1[i]&&len>mx2[j])
            {
                len=max(mx1[i],mx2[j])+1;
                if(len<ans) ans=len;
            }
        }
    }
    if(ans==inf) ans=-1;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str1);
    scanf("%s",str2);
    n=strlen(str1);
    m=strlen(str2);
    int ans=solve();
    printf("%d\n",ans);
    return 0;
}
