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
typedef unsigned long long ll;
const int maxn=22;
ll dp[22][22];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        dp[i][0]=1;
        for(int j=1;j<maxn;++j)
            dp[i][j]=dp[i-1][j-1]*(i-1)+dp[i-1][j];
    }
    int n,k;
    while(cin>>n>>k)
    {
        if(n==0&&k==0) break;
        cout<<dp[n][k]<<endl;
    }
    return 0;
}
