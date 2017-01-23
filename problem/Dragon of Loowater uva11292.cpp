#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
int d[20001],k[20001];
int main()
{
	int n,m,i,j;
	while(~scanf("%d%d",&n,&m))
	{
		if(n==0&&m==0)
		{break;}
		for(i=0;i<n;++i)
		{
			scanf("%d",&d[i]);
		}
		for(i=0;i<m;++i)
		{
			scanf("%d",&k[i]);
		}
		sort(d,d+n);
		sort(k,k+m);
		int sum=0;
		bool flag=true;
		j=0;
		for(i=0;i<n;++i)
		{
			while(k[j]<d[i]&&j<m)
			{
				j++;
			}
			if(j==m)
			{
				flag=false;
				break;
			}
			sum+=k[j];
			j++;
		}
		if(flag)
			printf("%d\n",sum);
		else
			printf("Loowater is doomed!\n");
	}
    return 0;  
}