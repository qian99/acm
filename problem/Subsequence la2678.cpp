#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
int num[100005];
int main()
{
	int i,j,n,s,temp;
	while(~scanf("%d%d",&n,&s))
	{
		num[0]=0;
		for(i=1;i<=n;++i)
		{
			scanf("%d",&temp);
			num[i]=num[i-1]+temp;
		}
		j=1;
		int res=n+1;
		for(i=1;i<=n;i++)
		{
			if(num[i]-num[j]<s)
			{
				continue;
			}
			while(num[i]-num[j+1]>=s)
			{
				j++;
			}
			if(i-j<res)
			{
				res=i-j;
			}
		}
		printf("%d\n",res%(n+1));
	}
    return 0;  
}