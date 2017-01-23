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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
const int mod=1000000009;
ll dp[maxn][maxn],C[maxn][maxn];
char strA[maxn],strB[maxn];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=C[i-1][j-1]+C[i-1][j];
            if(C[i][j]>=mod) C[i][j]-=mod;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n,K,m;
    while(~scanf("%d%d%d",&n,&K,&m))
    {
        scanf("%s",strA);
        scanf("%s",strB);
        memset(dp,0,sizeof(dp));
        int sum=0;
        for(int i=0;i<n;++i)
            sum+=strA[i]!=strB[i];
        dp[0][sum]=1;
        for(int i=0;i<K;++i)
            for(int j=0;j<=n;++j)
            {
                if(dp[i][j]==0) continue;
                for(int k=0;k<=m;++k)
                {
                    if(j+m-2*k<0) continue;
                    dp[i+1][j+m-2*k]+=C[j][k]*C[n-j][m-k]%mod*dp[i][j]%mod;
                    dp[i+1][j+m-2*k]%=mod;
                }
            }
        printf("%lld\n",dp[K][0]);
    }
    return 0;
}