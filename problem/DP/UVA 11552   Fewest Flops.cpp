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
const int maxn=1000+10;
char str[maxn];
int dp[maxn][26];
bool exits[maxn][26];
int cnt[maxn],minext[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int k;
        scanf("%d",&k);
        scanf("%s",str);
        memset(dp,0xff,sizeof(dp));
        memset(exits,0,sizeof(exits));
        memset(cnt,0,sizeof(cnt));
        int len=strlen(str);
        int seg=len/k;
        for(int i=0;i<len;i+=k)
          for(int j=i;j<i+k;++j)
              if(!exits[i/k+1][str[j]-'a'])
              {
                  cnt[i/k+1]++;
                  exits[i/k+1][str[j]-'a']=true;
              }
        memset(exits[0],1,sizeof(exits[0]));
        memset(dp[0],0,sizeof(dp[0]));
        minext[0]=0;
        for(int i=1;i<=seg;++i)
        {
            minext[i]=inf;
            for(int j=0;j<26;++j)
              if(exits[i][j])
               for(int k=0;k<26;++k)
                 if(exits[i][k])
                 {
                     if(j==k&&cnt[i]!=1) continue;
                     if(dp[i][k]==-1)
                        dp[i][k]=minext[i-1]+cnt[i];
                     else
                        dp[i][k]=min(dp[i][k],minext[i-1]+cnt[i]);
                    if(dp[i-1][j]!=-1)
                        dp[i][k]=min(dp[i][k],dp[i-1][j]+cnt[i]-1);
                    minext[i]=min(minext[i],dp[i][k]);
                 }
        }
        printf("%d\n",minext[seg]+1);
    }
    return 0;
}
