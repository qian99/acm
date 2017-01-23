#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int a[55][55],n,m,p,q;
ll dp[12][1<<10],dp2[12][1<<10];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&p))
    {
        memset(a,0,sizeof(a));
        int x,y;
        scanf("%d",&q);
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=1;
        }
        if(n>m||n>p)
        {
            printf("0\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        int total=1<<m;
        for(int i=1;i<=n;++i)
            for(int j=0;j<total;++j)
                for(int k=0;k<m;++k)
                {
                    if(!a[i][k+n+1]&&!(j&(1<<k)))
                        dp[i][j|(1<<k)]+=dp[i-1][j];
                }
        int cat[15],cnt=0;
        ll res=0;
        for(int i=0;i<total;++i)
        {
            cnt=0;
            for(int j=0;j<m;++j)
                if(i&(1<<j)) cat[++cnt]=j;
            if(cnt!=n) continue;
            memset(dp2,0,sizeof(dp2));
            dp2[0][0]=1;
            for(int j=1;j<=n;++j)
                for(int k=0;k<(1<<p);++k)
                    for(int l=0;l<p;++l)
                    {
                        if(!a[cat[j]+n+1][l+n+m+1]&&!(k&(1<<l)))
                            dp2[j][k|(1<<l)]+=dp2[j-1][k];
                    }
            ll tmp=0;cnt=0;
            for(int j=0;j<(1<<p);++j)
            {
                cnt=0;
                for(int k=0;k<p;++k)
                    if(j&(1<<k)) cnt++;
                if(cnt==n) tmp+=dp2[n][j];
            }
            res+=tmp*dp[n][i];
        }
        printf("%lld\n",res);
    }
    return 0;
}

