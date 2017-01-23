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

const int maxn=1000+10;
int dp[maxn],cal[maxn];

int main()
{
    int m,n,t;
    while(~scanf("%d%d",&n,&t))
    {
        int sum=0;
        int p,q;
        memset(dp,0,sizeof(dp));
        memset(cal,0,sizeof(dp));
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&p,&q);
            sum+=p;
            if(q>p)
            {
                cal[q-p]++;
            }
        }
        dp[1000]=sum;
        for(int i=999;i>0;--i)
        {
            dp[i]=dp[i+1]+cal[i+1];
            cal[i]=cal[i]+cal[i+1];
        }
        while(t--)
        {
            scanf("%d",&m);
            printf("%d\n",dp[m]);
        }
    }
    return 0;
}
