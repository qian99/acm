#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int maxn=11;
typedef long long ll;
ll dp[maxn][maxn*maxn][1<<10];
int n,k;
inline bool check(int s,int p)
{
	return !(s&(1<<p));
}
void dfs(int line,int p,int st,int snext,int cnt,ll val)
{
	if(p==n)
	{
		dp[line+1][cnt][snext]+=val;
		return ;
	}
	dfs(line,p+1,st,snext,cnt,val);
	if(check(st,p)&&cnt<k)
	{
		int state=1<<p;
		if(p>0) state|=1<<(p-1);
		if(p<n-1) state|=1<<(p+1);
		dfs(line,p+1,st|state,snext|state,cnt+1,val);
	}
}
int main()
{
	while(cin>>n>>k)
	{
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		for(int i=0;i<n;++i)
			for(int j=0;j<=k;++j)
				for(int x=0;x<(1<<n);++x)
					if(dp[i][j][x]) dfs(i,0,x,0,j,dp[i][j][x]);

		ll ans=0;
		for(int y=0;y<(1<<n);++y)
			ans+=dp[n][k][y];
		//printf("%I64d\n",ans);
		cout<<ans<<endl;
	}
	return 0;
}