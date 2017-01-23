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
const int maxn=1000+10;
const int mod=1000000000+7;
ll dp[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    dp[1]=1;
    for(int i=2;i<=1000;++i)
    {
        int m=i-1;
        for(int j=i-1;j>=1;--j)
        {
            if(m%j==0)
             dp[i]=(dp[i]+dp[j])%mod;
        }
    }
    int n,tcase=0;
    while(~scanf("%d",&n))
    {
        tcase++;
        printf("Case %d: %I64d\n",tcase,dp[n]);
    }
    return 0;
}
