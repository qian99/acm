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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll dp[35];
ll f(int n,int k)
{
    if(n==0) return k>=1;
    if(dp[n]!=-1&&(1<<n)==k) return dp[n];
    n--;
    if(k<=(1<<n)) return f(n,k)*2;
    dp[n]=f(n,1<<n);
    return dp[n]*2+f(n,k-(1<<n));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int t,tcase=0;
    scanf("%d",&t);
    int K,A,B;
    while(t--)
    {
        scanf("%d%d%d",&K,&A,&B);
        ll ans=f(K,B)-f(K,A-1);
        printf("Case %d: %lld\n",++tcase,ans);
    }
    return 0;
}
