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
int mw[25],mk[25],cnt[1<<10],n,k;
ll dp[25][1<<10];
void Init(int n)
{
    mw[n]=n,mk[n]=0;
    if(n>1)
    {
        mw[n-1]=n-1;mk[n-1]=0;
        mw[n+1]=n-1;mk[n+1]=0;
    }
    for(int i=n-2;i>=1;i--)
    {
        mw[i]=mw[i+2]-2;
        mk[i]=mk[i+2]+1;
    }
    for(int i=n+2;i<n*2;i++)
    {
        mw[i]=mw[i-2]-2;
        mk[i]=mk[i-2]+1;
    }
    for(int i=0;i<(1<<10);++i)
    {
        int x=i;
        cnt[i]=0;
        while(x)
        {
            cnt[i]++;
            x=x&(x-1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cin>>n>>k;
    Init(n);
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    dp[1][0]=1;
    dp[1][1<<mk[1]]=1;
    for(int i=0;i<n*2;++i)
        for(int x=0;x<(1<<n);++x)
        {
            if(dp[i][x]==0) continue;
            dp[i+2][x]+=dp[i][x];
            for(int j=mk[i+2];j<mk[i+2]+mw[i+2];++j)
            {
                if(!(x&(1<<j)))
                    dp[i+2][x|(1<<j)]+=dp[i][x];
            }
        }
    ll ans=0;
    for(int i=0;i<(1<<n);++i)
        for(int j=0;j<(1<<n);++j)
            if(cnt[i]+cnt[j]==k)
                ans+=dp[n*2-1][i]*dp[n*2-2][j];
    cout<<ans<<endl;
    return 0;
}
