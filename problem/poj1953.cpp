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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;

//const int maxn=10000+10;
int dp[50];

int main()
{
    dp[1]=2;
    dp[2]=3;
    for(int i=3;i<=45;++i)
    {
        dp[i]=dp[i-1]+dp[i-2];
    }
    int t,n,tcase=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        printf("Scenario #%d:\n",tcase);
        printf("%d\n\n",dp[n]);
        tcase++;
    }
    return 0;
}