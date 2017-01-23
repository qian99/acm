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
const int maxn=30;
int dp[maxn][maxn][maxn][maxn];
int sum1[maxn],sum2[maxn];
int f(int l1,int r1,int l2,int r2)
{
    if(dp[l1][r1][l2][r2]>=0) return dp[l1][r1][l2][r2];
    if(l1>r1&&l2>r2) return dp[l1][r1][l2][r2]=0;
    int ret=0;
    int sum=sum1[r1]-sum1[l1-1]+sum2[r2]-sum2[l2-1];
    if(l1<=r1)
    {
        ret=max(ret,sum-f(l1+1,r1,l2,r2));
        ret=max(ret,sum-f(l1,r1-1,l2,r2));
    }
    if(l2<=r2)
    {
        ret=max(ret,sum-f(l1,r1,l2+1,r2));
        ret=max(ret,sum-f(l1,r1,l2,r2-1));
    }
    dp[l1][r1][l2][r2]=ret;
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        sum1[0]=sum2[0]=0;
        for(int i=1;i<=n;++i)
        {
            cin>>sum1[i];
            sum1[i]+=sum1[i-1];
        }
        for(int i=1;i<=n;++i)
        {
            cin>>sum2[i];
            sum2[i]+=sum2[i-1];
        }
        memset(dp,0xff,sizeof(dp));
        cout<<f(1,n,1,n)<<endl;
    }
    return 0;
}
