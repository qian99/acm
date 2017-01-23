/*
枚举任意两个数，及其第几次出现，然后求去掉这两个数时的方案数
确定了枚举的两个数及其出现的次数，那么剩下的由什么组成对结果没影响
最后需要优化一下sum[i][j]表示取得第一个数总和为i时，取j的总和
*/
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
int dp[maxn],dislike[maxn],sum[maxn][maxn];
int gval[maxn][maxn];
int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }
void Init(int n)
{
    for(int i=0;i<=n;++i) dp[i]=0;
    dp[0]=1;
    for(int i=1;i<n;++i)
    {
        if(dislike[i]) continue;
        for(int j=i;j<=n;++j)
        {
            dp[j]+=dp[j-i];
            if(dp[j]>=mod) dp[j]-=mod;
        }
    }
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            sum[i][j]=0;
    for(int i=1;i<n;++i)
        for(int j=1;j<n;++j)
        if(!dislike[j])
        for(int k=j;i+k<=n;k+=j)
        {
            sum[i][j]+=dp[n-i-k];
            if(sum[i][j]>=mod) sum[i][j]-=mod;
        }
}
int solve(int n)
{
    int ans=0;
    for(int i=1;i<n;++i)
        if(!dislike[i])
        for(int x=i;x<n;x+=i)
        {
            for(int j=i;x+j<=n;++j)
                if(!dislike[j])
                {
                    ans+=(ll)sum[x][j]*gval[i][j]%mod;
                    if(ans>=mod) ans-=mod;
                }
        }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            gval[i][j]=gcd(i,j);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(dislike,0,sizeof(dislike));
        int val;
        for(int i=0;i<m;++i)
        {
            scanf("%d",&val);
            dislike[val]=1;
        }
        Init(n);
        int ans=solve(n);
        printf("%d\n",ans);
    }
    return 0;
}
