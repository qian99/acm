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
const int maxn=5000;
const int mod=100000000;
int limit[20],state[maxn],dp[20][maxn],top,total;
void getstate(int n)
{
    top=0;
    total=1<<n;
    for(int i=0;i<total;++i)
    {
        if(i&(i<<1)) continue;
        state[top++]=i;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&m,&n))
    {
        int temp;
        for(int i=1;i<=m;++i)
        {
            int sum=0;
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&temp);
                sum=(sum<<1)+temp;
            }
            limit[i]=sum;
        }
        getstate(n);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<top;++i) dp[1][state[i]]=((state[i]|limit[1])==limit[1]);
        for(int i=2;i<=m;++i)
        {
            for(int j=0;j<top;++j)
            {
                if((state[j]|limit[i])!=limit[i]) continue;
                for(int k=0;k<top;++k)
                {
                    if(dp[i-1][state[k]]==0) continue;
                    if(state[j]&state[k]) continue;
                    dp[i][state[j]]+=dp[i-1][state[k]];
                    dp[i][state[j]]%=mod;
                }
            }
        }
        int ans=0;
        for(int i=0;i<top;++i)
        {
            ans+=dp[m][state[i]];
            ans%=mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}
