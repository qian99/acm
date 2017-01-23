#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
char square[15][15];
int rule[4][2]={0,1,1,0,-1,0,0,-1};
int n;
bool check(int x,int y,char c);
int main()
{
	int t,casenum;
	scanf("%d",&t);
	casenum=1;
	while(t--)
	{
		int i,j,k;
		scanf("%d",&n);
		for(i=0;i<n;++i)
		{
			scanf("%s",square[i]);
		}
		for(i=0;i<n;++i)
		{
			for(j=0;j<n;++j)
			{
				if(square[i][j]=='.')
				{
					char temp='A';
					for(k=0;k<26;++k)
					{
						if(check(i,j,temp+k))
							break;
					}
					square[i][j]=temp+k;
				}
			}
		}
		printf("Case %d:\n",casenum);
		for(i=0;i<n;++i)
		{
			printf("%s\n",square[i]);
		}
		casenum++;
	}
    return 0;  
}
bool check(int x,int y,char c)
{
	for(int i=0;i<4;++i)
	{
		int px=x+rule[i][0];
		int py=y+rule[i][1];
		if(x>=0&&x<n&&y>=0&&y<n&&c==square[px][py])
		{
			return false;
		}
	}
	return true;
}