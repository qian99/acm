#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=110000;
int xb[11][maxn];
int dp[2][15];
bool canreach[11];
int main()
{
    int t,n;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        int np,tp;
        t=0;
        memset(xb,0,sizeof(xb));
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&np,&tp);
            t=max(tp,t);
            xb[np][tp]++;
        }
        memset(canreach,false,sizeof(canreach));
        memset(dp,0,sizeof(dp));
        int st=4,ed=6;
        canreach[4]=canreach[6]=canreach[5]=true;
        dp[1][4]=xb[4][1];
        dp[1][5]=xb[5][1];
        dp[1][6]=xb[6][1];
        for(int i=2;i<=t;++i)
        {
            /*if(i<=5)
            {
                st--;ed++;
                canreach[st]=canreach[ed]=true;
            */
            int u=i%2;
            for(int j=0;j<=10;++j)
            {
                if(canreach[j]||(j-1>=0&&canreach[j-1])||(j+1<=10&&canreach[j+1]))
                {
                    int k=j-1;
                    if(k>=0&&canreach[k])
                      dp[u][j]=max(dp[u^1][k],dp[u^1][j])+xb[j][i];
                    k=j+1;
                    if(k<=10&&canreach[k])
                      dp[u][j]=max(dp[u][j],max(dp[u^1][k],dp[u^1][j])+xb[j][i]);
                }
            }
            if(i<=5)
            {
                st--;ed++;
                canreach[st]=canreach[ed]=true;
            }
        }
        int maxx=0;
        for(int i=0;i<=10;++i)
        {
            maxx=max(maxx,dp[t%2][i]);
        }
        printf("%d\n",maxx);
    }
    return 0;
}
