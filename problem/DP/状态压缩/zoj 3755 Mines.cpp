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
int dp[15][1<<10];
int a[15][15],num[1<<10][15],cnt[1<<10];
int n,m;
void cal()
{
    memset(num,0,sizeof(num));
    memset(cnt,0,sizeof(cnt));
    int total=1<<n;
    for(int i=0;i<total;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i&(1<<j))
            {
                cnt[i]++;
                if(j) num[i][j-1]++;
                num[i][j]++;
                num[i][j+1]++;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        int total=1<<n;
        memset(dp,0xff,sizeof(dp));
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                scanf("%d",&a[i][j]);
        cal();
        bool flag;
        for(int i=0;i<total;++i)
        {
            flag=true;
            for(int j=0;j<n;++j)
                if(num[i][j]>a[j][0]) {flag=false;break;}
            if(flag) dp[0][i]=cnt[i];
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=0;j<total;++j)
            {
                if(dp[i-1][j]==-1) continue;
                for(int k=0;k<total;++k)
                {
                    flag=true;
                    for(int z=0;z<n;++z)
                        if(num[j][z]+num[k][z]!=a[z][i-1])
                        {flag=false;break;}
                    if(flag)
                    {
                        if(dp[i][k]==-1) dp[i][k]=dp[i-1][j]+cnt[k];
                        else dp[i][k]=min(dp[i][k],dp[i-1][j]+cnt[k]);
                    }
                }
            }
        }
        int ans=inf;
        for(int i=0;i<total;++i)
        {
            if(dp[m][i]!=-1)
                ans=min(ans,dp[m][i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

