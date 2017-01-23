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
const int maxn=50000+10;
ll val[maxn],dp[maxn][2],dp2[maxn][2],a[maxn];
int n,T,S;
ll solve(int flag)
{
    ll maxv=-1,sum=0,tmp;
    int t;
    val[2]=a[2];val[n]=a[n];
    if(flag) val[2]=val[n]=0;
    if(flag) sum=a[1];//第一个位置取
    else sum=0;  //第一个位置不取
    dp[2][0]=0;dp[2][1]=val[2];
    for(int i=3;i<=n;++i)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
        dp[i][1]=dp[i-1][0]+val[i];
    }
    dp2[n][0]=0;dp2[n][1]=val[n];
    for(int i=n-1;i>=2;--i)
    {
        dp2[i][0]=max(dp2[i+1][0],dp2[i+1][1]);
        dp2[i][1]=dp2[i+1][0]+val[i];
    }
    //顺时针枚举
    tmp=0;
    for(int i=2;i<=n&&(i-1)<=T;++i)
    {
        t=i-1;
        tmp=max(dp[i][0],dp[i][1]);
        maxv=max(maxv,sum+tmp);
        t*=2;
        if(t>=T||i==n) continue;
        int p=(n+1)-(T-t);
        if(p<=i+1) p=i+2;
        if(p>n) continue;
        tmp+=max(dp2[p][0],dp2[p][1]);
        maxv=max(maxv,sum+tmp);
    }
    //逆时针枚举
    tmp=0;
    for(int i=n;i>=2&&(n+1-i)<=T;--i)
    {
        t=(n+1-i);
        tmp=max(dp2[i][0],dp2[i][1]);
        maxv=max(maxv,tmp+sum);
        t*=2;
        if(t>=T||i==2) continue;
        int p=(T-t)+1;
        if(p>=i-1) p=i-2;
        if(p<=1) continue;
        tmp+=max(dp[p][0],dp[p][1]);
        maxv=max(maxv,tmp+sum);
    }
    return maxv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&T,&S))
    {
        for(int i=1;i<=n;++i)
            scanf("%lld",&a[i]);
        int cnt=0;
        for(int i=S;i<=n;++i) val[++cnt]=a[i];
        for(int i=1;i<S;++i) val[++cnt]=a[i];
        for(int i=1;i<=n;++i) a[i]=val[i];
        ll ans=max(solve(0),solve(1));
        printf("%lld\n",ans);
    }
    return 0;
}
