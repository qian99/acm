#include <iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<stack>
#include<queue>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define pi acos(-1.0)
using namespace std;
const int maxn=1<<20;
int dp[maxn],d[25][25],pre[maxn];
string sq[maxn];
int pt[25][2];
int res[25];
inline int Len(int x1,int y1,int x2,int y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int sx,sy;
        int n;
        scanf("%d%d",&sx,&sy);
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%d%d",&pt[i][0],&pt[i][1]);
        pt[n][0]=sx;pt[n][1]=sy;
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                d[i][j]=Len(pt[i][0],pt[i][1],pt[j][0],pt[j][1]);
        dp[0]=0;
        int tmp;
        int st;
        for(int i=1;i<(1<<n);++i)
        {
            dp[i]=inf;
            for(int j=0;j<n;++j)
            {
                if(!(i&(1<<j))) continue;
                st=i^(1<<j);
                tmp=dp[st]+d[j][n]+d[j][n];
                if(tmp<dp[i])
                {
                    dp[i]=tmp;
                    pre[i]=st;
                }
                for(int k=j+1;k<n;++k)
                if(i&(1<<k))
                {
                    st=i^(1<<j)^(1<<k);
                    tmp=dp[st]+d[j][n]+d[j][k]+d[k][n];
                    if(tmp<dp[i])
                    {
                        dp[i]=tmp;
                        pre[i]=st;
                    }
                }
            }
        }
        printf("Case %d:\n",++tcase);
        printf("%d\n",dp[(1<<n)-1]);
        int tot=0;
        st=(1<<n)-1;
        while(st)
        {
            int x=pre[st]^st;
            for(int i=0;i<n;++i)
                if(x&(1<<i))
                    res[tot++]=i+1;
            st=pre[st];
        }
        for(int i=0;i<tot;++i)
        {
            if(i) printf(" ");
            printf("%d",res[i]);
        }
        printf("\n");
    }
    return 0;
}
