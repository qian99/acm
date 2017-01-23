#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
const int mod=1000000007;
ll dp[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        dp[1][i]=1;
    for(int i=1;i<k;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int x=j;x<=n;x+=j)
            {
                dp[i+1][x]+=dp[i][j];
                if(dp[i+1][x]>=mod) dp[i+1][x]-=mod;
            }
        }
    }
    ll ans=0;
    for(int i=1;i<=n;++i)
    {
        ans+=dp[k][i];
        if(ans>=mod) ans-=mod;
    }
    cout<<ans<<endl;
    return 0;
}