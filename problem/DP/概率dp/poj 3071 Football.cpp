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
const int maxn=1<<8;
double dp[maxn<<2][maxn],p[maxn][maxn];
void build(int l,int r,int rt)
{
    memset(dp[rt],0,sizeof(dp[rt]));
    if(l==r)
    {
        dp[rt][l]=1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    double tmp;
    for(int i=l;i<=m;++i)
    {
        tmp=dp[rt<<1][i];
        for(int j=m+1;j<=r;++j)
            dp[rt][i]+=tmp*dp[rt<<1|1][j]*p[i][j];
    }
    for(int i=m+1;i<=r;++i)
    {
        tmp=dp[rt<<1|1][i];
        for(int j=l;j<=m;++j)
            dp[rt][i]+=tmp*dp[rt<<1][j]*p[i][j];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==-1) break;
        n=1<<n;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%lf",&p[i][j]);
        build(1,n,1);
        double maxp=-1;
        int ans=1;
        for(int i=1;i<=n;++i)
            if(dp[1][i]>maxp)
            {
                maxp=dp[1][i];
                ans=i;
            }
        printf("%d\n",ans);
    }
    return 0;
}
