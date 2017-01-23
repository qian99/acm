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
int dp[2][1<<8][1<<8],mk[77];
char a[77][8];
int m,n;
bool check(int state,int p)
{
    return !((1<<p)&state);
}
void dfs(int lst,int now,int nxt,int p,int wh,int step)
{
    if(p==n)
    {
        dp[wh][now][nxt]=min(dp[wh][now][nxt],step);
        return ;
    }
    if(now&(1<<p)) dfs(lst,now,nxt,p+1,wh,step);
    else
    {
        int tmp=now|(1<<p);
        if(p+1<n&&check(now,p+1))
          dfs(lst,tmp|(1<<(p+1)),nxt,p+1,wh,step+1);
        if(check(nxt,p))
          dfs(lst,tmp,nxt|(1<<p),p+1,wh,step+1);
        if(!check(lst,p))
        {
            if(p==0||!check(now,p-1))
               dfs(lst,now,nxt,p+1,wh,step);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&m,&n);
    memset(mk,0,sizeof(mk));
    for(int i=0;i<m;++i)
    {
        scanf("%s",a[i]);
        for(int j=0;j<n;++j)
          if(a[i][j]=='*') mk[i]|=(1<<j);
    }
    int total=1<<n;
    int wk=0;
    memset(dp[1],0x3f,sizeof dp[1]);
    dp[1][total-1][mk[0]]=0;
    for(int i=0;i<m;++i)
    {
        memset(dp[wk],0x3f,sizeof(dp[wk]));
        for(int j=0;j<total;++j)
        {
            for(int k=0;k<total;++k)
            {
                if(dp[wk^1][j][k]==inf) continue;
                dfs(j,k,mk[i+1],0,wk,dp[wk^1][j][k]);
            }
        }
        wk^=1;
    }
    int ans=inf;
    for(int i=0;i<total;++i)
       ans=min(ans,dp[wk^1][i][0]);
    printf("%d\n",ans);
    return 0;
}
