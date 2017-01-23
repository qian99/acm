#include <iostream>
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
const int maxn=1000000+10;
int dp[maxn],num[maxn],pre[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            dp[i]=pre[i]=0;
        }
        dp[0]=pre[0]=0;
        int k,maxv;
        for(int i=1;i<=m;++i)
        {
            maxv=-inf;
            for(int j=i;j<=n;++j)
            {
                dp[j]=max(dp[j-1],pre[j-1])+num[j];
                pre[j-1]=maxv;
                maxv=max(maxv,dp[j]);
            }
        }
        printf("%d\n",maxv);
    }
    return 0;
}
