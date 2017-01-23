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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
const int mod=1000000007;
int dp[maxn][maxn];
int main()
{
    //reopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,d;
    cin>>n>>k>>d;
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<=n;++j)
            for(int x=1;x<=min(i,k);++x)
            {
                if(x>=d&&j>=1)
                {
                    dp[i][j]+=dp[i-x][j-1];
                    if(dp[i][j]>=mod) dp[i][j]-=mod;
                }
                if(x<d)
                {
                    dp[i][j]+=dp[i-x][j];
                    if(dp[i][j]>=mod) dp[i][j]-=mod;
                }
            }
    int ans=0;
    for(int j=1;j<=n;++j)
    {
        ans+=dp[n][j];
        if(ans>=mod) ans-=mod;
    }
    cout<<ans<<endl;
    return 0;
}