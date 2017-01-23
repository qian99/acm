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
const int mod=1000000000+7;
int dp[maxn][1<<10][25];
int msk[maxn],n,m,C,D,total;
char str[55];
int getmsk()
{
    int res=0;
    for(int i=0;i<m;++i)
      if(str[i]=='0') res|=(1<<i);
    return res;
}
void dfs(int now,int nxt,int p,int k,int pos,int v)
{
    if(p==m)
    {
        dp[pos][nxt][k]+=v;
        dp[pos][nxt][k]%=mod;
        return ;
    }
    if((now&(1<<p))||(msk[pos]&(1<<p))) dfs(now|(1<<p),nxt,p+1,k,pos,v);
    else
    {
        if(k<D) dfs(now|(1<<p),nxt,p+1,k+1,pos,v);
        if(!(nxt&(1<<p))) dfs(now|(1<<p),nxt|(1<<p),p+1,k,pos,v);
        int st=now|(1<<p);
        if(p+1<m&&(!(now&(1<<(p+1)))))
           dfs(st|(1<<(p+1)),nxt,p+1,k,pos,v);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d%d",&n,&m,&C,&D))
    {
        total=1<<m;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            msk[i]=getmsk();
        }
        memset(dp,0,sizeof(dp));
        dp[0][msk[1]][0]=1;
        msk[0]=msk[n+1]=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<total;++j)
            {
                for(int k=0;k<=D;++k)
                {
                    if(!dp[i-1][j][k]) continue;
                    dfs(j,msk[i+1],0,k,i,dp[i-1][j][k]);
                }
            }
        }
        int ans=0;
        for(int j=C;j<=D;++j)
        {
            ans+=dp[n][0][j];
            ans%=mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}
