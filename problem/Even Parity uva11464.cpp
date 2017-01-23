#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
const int Inf=99999999;
int a[20][20],b[20][20];
int n,minstep,fchange;
void dfs(int s);
int create();
int main()
{
	int t,r;
	scanf("%d",&t);
	r=1;
	while(t--)
	{
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=n;++j)
			{
				scanf("%d",&a[i][j]);
			}
		}
		minstep=Inf;
		fchange=0;
		dfs(1);
		if(minstep==Inf)
		{
			printf("Case %d: -1\n",r);
		}
		else
		{
			printf("Case %d: %d\n",r,minstep);
		}
		r++;
	}
    return 0;  
}
void dfs(int s)
{
	if(s>n)
	{
		int temp=create();
		if(temp+fchange<minstep)
		{
			minstep=temp+fchange;
		}
		return ;
	}
	if(a[1][s]==0)
	{
		b[1][s]=0;
		dfs(s+1);
		b[1][s]=1;
		fchange++;
		dfs(s+1);
		fchange--;
		b[1][s]=0;
	}
	else
	{
		b[1][s]=1;
		dfs(s+1);
	}
}
int create()
{
	int sum=0;
	int i,j,k;
	for(i=1;i<n;++i)
	{
		for(j=1;j<=n;++j)
		{
			k=b[i-1][j]+b[i][j-1]+b[i][j+1];
			if(k%2==0)
			{
				if(a[i+1][j]==1)
				{
					return Inf;
				}
				b[i+1][j]=0;
			}
			else
			{
				if(a[i+1][j]==0)
				{
					sum++;
				}
				b[i+1][j]=1;
			}
		}
	}
	for(i=1;i<=n;++i)
	{
		k=b[n-1][i]+b[n][i-1]+b[n][i+1];
		if(k%2!=0)
		{
			return Inf;
		}
	}
	return sum;
}
