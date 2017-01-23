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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
char str1[maxn],str2[maxn];
int dp[maxn][12][12];
int cal(int ca,int cb,int k)
{
    if(k==0)
      return ((cb-ca)%10+10)%10;
    return (((ca-cb))%10+10)%10;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y,a,b,c,d;
    while(~scanf("%s%s",str1,str2))
    {
        int n=strlen(str1);
        memset(dp,0x3f,sizeof(dp));
        str1[n]=str2[n]=str1[n+1]=str2[n+1]='0';
        x=str1[1]-'0';y=str1[2]-'0';
        a=cal(str1[0]-'0',str2[0]-'0',0);
        b=cal(str1[0]-'0',str2[0]-'0',1);
        dp[0][x][y]=min(a,b);
        for(int j=0;j<=a;++j)
          for(int k=0;k<=j;++k)
          {
              c=(x+j)%10;d=(y+k)%10;
              dp[0][c][y]=min(dp[0][c][y],a);
              dp[0][c][d]=min(dp[0][c][d],a);
          }
        for(int j=0;j<=b;++j)
          for(int k=0;k<=j;++k)
          {
              c=((x-j)%10+10)%10;d=((y-k)%10+10)%10;
              dp[0][c][y]=min(dp[0][c][y],b);
              dp[0][c][d]=min(dp[0][c][d],b);
          }
        for(int i=1;i<n;++i)
        {
            for(int j=0;j<10;++j)
            {
                for(int k=0;k<10;++k)
                {
                    if(dp[i-1][j][k]==inf) continue;
                    x=k;y=str1[i+2]-'0';
                    a=cal(j,str2[i]-'0',0);
                    b=cal(j,str2[i]-'0',1);
                    dp[i][x][y]=min(dp[i-1][j][k]+a,dp[i][x][y]);
                    dp[i][x][y]=min(dp[i-1][j][k]+b,dp[i][x][y]);
                    for(int q=0;q<=a;++q)
                      for(int w=0;w<=q;++w)
                      {
                          c=(x+q)%10;d=(y+w)%10;
                          dp[i][c][y]=min(dp[i][c][y],dp[i-1][j][k]+a);
                          dp[i][c][d]=min(dp[i][c][d],dp[i-1][j][k]+a);
                      }
                    for(int q=0;q<=b;++q)
                      for(int w=0;w<=q;++w)
                      {
                          c=((x-q)%10+10)%10;d=((y-w)%10+10)%10;
                          dp[i][c][y]=min(dp[i][c][y],dp[i-1][j][k]+b);
                          dp[i][c][d]=min(dp[i][c][d],dp[i-1][j][k]+b);
                      }
                }
            }
        }
        int ans=inf;
        for(int i=0;i<10;++i)
          for(int j=0;j<10;++j)
          {
              ans=min(ans,dp[n-1][i][j]);
          }
        printf("%d\n",ans);
    }
    return 0;
}
