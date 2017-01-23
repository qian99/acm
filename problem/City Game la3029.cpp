#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
#include<vector>
using namespace std;
const int maxn=1000+10;
char a[maxn][maxn];
int up[maxn][maxn],leftn[maxn][maxn],rightn[maxn][maxn];
int max(int a,int b);
int min(int a,int b);
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int m,n,i,j,k;
		scanf("%d%d",&m,&n);
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				char cp=getchar();
				while(cp!='R'&&cp!='F')
					cp=getchar();
				a[i][j]=cp;
			}
		}
		int ans=0;
		for(i=0;i<m;i++)
		{
			int lf=-1,rf=n;
			for(j=0;j<n;j++)
			{
				if(a[i][j]=='F')
				{
					if(i==0)
					{
						up[i][j]=1;
						leftn[i][j]=lf+1;
					}
					else
					{
						up[i][j]=up[i-1][j]+1;
						leftn[i][j]=max(leftn[i-1][j],lf+1);
					}
					
				}
				else
				{
					up[i][j]=0;
					leftn[i][j]=0;
					lf=j;
				}
			}
			for(k=n-1;k>=0;k--)
			{
				if(a[i][k]=='F')
				{
					if(i==0)
					{
						rightn[i][k]=rf-1;
					}
					else
					{
						rightn[i][k]=min(rightn[i-1][k],rf-1);
					}
					ans=max(ans,up[i][k]*(rightn[i][k]-leftn[i][k]+1));
				}
				else
				{
					rightn[i][k]=n;
					rf=k;
				}
			}
		}
		printf("%d\n",ans*3);
	}
	return 0;
}
int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a<b?a:b;
}
/*int up[1005][1005],leftn[1005][1005],rightn[1005][1005];
int main()
{
	int t,m,n;
	scanf("%d",&t);
	while(t--)
	{
		int i,j,k;
		scanf("%d%d",&m,&n);
		char cp;
		for(i=0;i<m;++i)
		{
			for(j=0;j<n;++j)
			{
				cp=getchar();
				while(cp!='R'&&cp!='F')
					cp=getchar();
				a[i][j]=cp;
			}
		}
		int lf,rf,ans=0;
		for(i=0;i<m;++i)
		{
			lf=-1,rf=n;
			for(j=0;j<n;++j)
			{
				if(a[i][j]=='F')
				{
					if(i==0)
					{
						up[i][j]=1;
						leftn[i][j]=lf+1;
						continue;
					}
					up[i][j]=up[i-1][j]+1;
					if((lf+1)>leftn[i-1][j])
					{
						leftn[i][j]=lf+1;
					}
					else
					{
						leftn[i][j]=leftn[i-1][j];
					}
					
				}
				else
				{
					up[i][j]=0;
					leftn[i][j]=0;
					lf=j;
				}
			}
			for(k=n-1;k>=0;--k)
			{
				if(a[i][k]=='F')
				{
				
					
					if(i==0)
					{
						rightn[i][k]=rf-1;
					}
					else
					{
						if((rf-1)<rightn[i-1][k])
						{
							rightn[i][k]=rf-1;
						}
						else
						{
							rightn[i][k]=rightn[i-1][k];
						}
					}
					if(ans<up[i][k]*(rightn[i][k]-leftn[i][k]+1))
					{
						ans=up[i][k]*(rightn[i][k]-leftn[i][k]+1);
					}
				}
				else
				{
					rightn[i][j]=n;
					rf=k;
				}
			}
		}
		printf("%d\n",ans*3);
	}
    return 0;
}*/
