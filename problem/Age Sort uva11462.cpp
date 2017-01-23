#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
int age[105];
int main()
{
	int n,temp;
	while(~scanf("%d",&n))
	{
		if(n==0)
		{break;}
		memset(age,0,sizeof(age));
		for(int i=0;i<n;++i)
		{
			scanf("%d",&temp);
			age[temp]++;
		}
		bool flag=true;
		for(int j=1;j<=100;++j)
		{
			for(int k=0;k<age[j];++k)
			{
				if(flag)
				{
					printf("%d",j);
					flag=false;
				}
				else
				{
					printf(" %d",j);
				}
			}
		}
		printf("\n");
	}
    return 0;  
}