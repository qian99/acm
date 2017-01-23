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
const int maxn=200000+10;
int num[maxn],dp[maxn][2],z[maxn];
int solve(int d[maxn][2],int u[maxn],int n)
{
    d[0][0]=d[0][1]=0;
    for(int i=1;i<=n;++i)
    {
        d[i][0]=max(d[i-1][1],d[i-1][0]);
        d[i][1]=d[i-1][0]+u[i];
    }
    return max(d[n][0],d[n][1]);
}
int main()
{
    int m,n;
    while(~scanf("%d%d",&m,&n))
    {
        int i,j;
        for(i=1;i<=m;++i)
        {
            for(j=1;j<=n;++j)
               scanf("%d",&num[j]);
            z[i]=solve(dp,num,n);
        }
        int ans=solve(dp,z,m);
        printf("%d\n",ans);
    }
    return 0;
}
