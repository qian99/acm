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
const int mod=1000000007;
const int maxn=700+10;
ll dp[maxn][maxn][9];
int con[9][2]={{0,1},{0,2},{2,0},{1,0},{0,0},{1,1},{1,2},{2,1},{2,2}};
int id[10][10];
int match[maxn],S[maxn],cnt,n;
bool flag[maxn][maxn];
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=0;i<9;++i)
        id[con[i][0]][con[i][1]]=i;
    while(~scanf("%s",str))
    {
        n=strlen(str);
        cnt=0;
        S[cnt++]=0;
        for(int i=1;i<n;++i)
            if(str[i]=='(') S[cnt++]=i;
            else
            {
                match[i]=S[cnt-1];
                match[S[cnt-1]]=i;
                cnt--;
            }
        memset(dp,0,sizeof(dp));
        memset(flag,0,sizeof(flag));
        for(int i=0;i<n-1;++i)
            if(match[i]==i+1)
            {
                dp[i][i+1][0]=dp[i][i+1][1]=dp[i][i+1][2]=dp[i][i+1][3]=1;
                flag[i][i+1]=true;
            }
        int l,r;
        for(int k=4;k<=n;++k)
            for(int i=0;i<=n-k;++i)
            {
                if(str[i]=='('&&str[i+k-1]==')'&&flag[i+1][i+k-2])
                    flag[i][i+k-1]=true;
                else
                {
                    l=i;r=match[i];
                    if(r<i+k-1&&flag[l][r]&&flag[r+1][i+k-1])
                        flag[i][i+k-1]=true;

                }
            }
        for(int k=4;k<=n;k+=2)
            for(int i=0;i<=n-k;++i)
                if(flag[i][i+k-1])
                {
                    if(str[i]=='('&&str[i+k-1]==')'&&flag[i+1][i+k-2])
                    {
                        for(int j=0;j<4;++j)
                        {
                            for(int x=0;x<9;++x)
                            {
                                if(con[j][0]!=0&&con[x][0]==con[j][0])
                                    continue;
                                if(con[j][1]!=0&&con[x][1]==con[j][1])
                                    continue;
                                dp[i][i+k-1][j]+=dp[i+1][i+k-2][x];
                                dp[i][i+k-1][j]%=mod;
                            }
                        }
                    }
                    else
                    {
                        l=i;r=match[i];
                        for(int j=0;j<9;++j)
                          for(int x=0;x<9;++x)
                          {
                              if(con[j][1]!=0&&con[x][0]==con[j][1])
                                continue;
                              dp[i][i+k-1][id[con[j][0]][con[x][1]]]+=dp[l][r][j]*dp[r+1][i+k-1][x];
                              dp[i][i+k-1][id[con[j][0]][con[x][1]]]%=mod;
                          }
                    }
                }
        ll ans=0;
        for(int i=0;i<9;++i)
            ans=(ans+dp[0][n-1][i])%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
