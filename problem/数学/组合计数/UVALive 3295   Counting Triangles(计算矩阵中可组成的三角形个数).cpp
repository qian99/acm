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
const int maxn=1000+10;
ll lcnt[maxn][maxn],dp[maxn][maxn];
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
void Init()
{
    memset(lcnt,0,sizeof(lcnt));
    memset(dp,0,sizeof(dp));
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            lcnt[i][j]=gcd(i,j)-1;
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            lcnt[i][j]+=lcnt[i-1][j];
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            lcnt[i][j]+=lcnt[i][j-1];
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+lcnt[i][j];
}
inline ll cal(int x)
{
    if(x<3) return 0;
    return (ll)x*(x-1)*(x-2)/6;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n,tcase=0;
    Init();
    while(~scanf("%d%d",&m,&n))
    {
        if(n==0&&m==0) break;
        tcase++;
        ll ans=cal((m+1)*(n+1))-(m+1)*cal(n+1)-(n+1)*cal(m+1)-dp[m][n]*2;
        printf("Case %d: %lld\n",tcase,ans);
    }
    return 0;
}
