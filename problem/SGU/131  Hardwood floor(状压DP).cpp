#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
ll dp[11][1<<10];
int m,n;
inline bool check(int state,int p)
{
    return !((state>>p)&1);
}
void dfs(int state,int nxts,int p,int k,ll v)
{
    if(p==n)
    {
        dp[k][nxts]+=v;
        return ;
    }
    if(state&(1<<p)) dfs(state,nxts,p+1,k,v);
    else
    {
        if(check(nxts,p))
        {
            dfs(state|(1<<p),nxts|(1<<p),p+1,k,v);
            int st=state|(1<<p);
            if(p+1<n&&check(state,p+1))
               dfs(st|(1<<(1+p)),nxts|(1<<p),p+1,k,v);
            st=nxts|(1<<p);
            if(p+1<n&&check(nxts,p+1))
               dfs(state|(1<<p),st|(1<<(1+p)),p+1,k,v);
            if(p-1>=0&&check(nxts,p-1))
               dfs(state|(1<<p),st|(1<<(p-1)),p+1,k,v);
        }
        if(p+1<n&&check(state,p+1))
        {
            dfs(state|(1<<(p+1)),nxts,p+1,k,v);
            if(check(nxts,p+1))
              dfs(state|(1<<(p+1)),nxts|(1<<(p+1)),p+1,k,v);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        int total=1<<n;
        memset(dp,0,sizeof(dp));
        dp[1][0]=1;
        for(int i=1;i<=m;++i)
        {
            for(int j=0;j<total;++j)
            {
                if(dp[i][j]) dfs(j,0,0,i+1,dp[i][j]);
            }
        }
        ll ans=dp[m+1][0];
        printf("%lld\n",ans);
    }
    return 0;
}
