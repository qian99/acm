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
const int maxn=100+10;
int a[maxn][maxn];
int dp[maxn<<1][maxn];
int num[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,x,y;
        scanf("%d%d",&n,&m);
        memset(a,0,sizeof(a));
        memset(dp,0xff,sizeof(dp));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=1;
        }
        for(int i=1;i<=n;++i) a[i][i]=1;
        int z;
        scanf("%d",&z);
        for(int i=1;i<=z;++i)
           scanf("%d",&num[i]);
        for(int i=1;i<=n;++i) dp[1][i]=1;
        dp[1][num[1]]=0;
       // int k;
        for(int i=2;i<=z;++i)
        {
            //k=num[i];
            for(int j=1;j<=n;++j)
            {
                for(int k=1;k<=n;++k)
                {
                    if(a[k][j]&&dp[i-1][j]!=-1)
                    {
                        if(dp[i][j]==-1)
                           dp[i][j]=dp[i-1][k]+(j==num[i]?0:1);
                        else
                           dp[i][j]=min(dp[i][j],dp[i-1][k]+(j==num[i]?0:1));
                    }
                }
            }
        }
        int ans=inf;
        for(int i=1;i<=n;++i)
           if(dp[z][i]!=-1) ans=min(ans,dp[z][i]);
        printf("%d\n",ans);
    }
    return 0;
}
