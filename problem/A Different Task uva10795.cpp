#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
int start[70],finish[70];
long long move(int *p,int i,int final);
int main()
{
	int i,n,casenum;
	casenum=1;
	while(~scanf("%d",&n))
	{
		if(n==0)
		{break;}
		for(i=1;i<=n;++i)
		{
			scanf("%d",&start[i]);
		}
		for(i=1;i<=n;++i)
		{
			scanf("%d",&finish[i]);
		}
		int k=n;
		while(k>=1&&start[k]==finish[k]) k--;
		long long ans=0;
		if(k>=1)
		{
			ans=move(start,k-1,6-start[k]-finish[k])+move(finish,k-1,6-start[k]-finish[k])+1;
		}
		printf("Case %d: %lld\n",casenum,ans);
		casenum++;
	}
    return 0;  
}
long long move(int *p,int i,int final)
{
	long long m=1;
	if(i==0)
		return 0;
	if(p[i]==final)
		return move(p,i-1,final);
	return move(p,i-1,6-p[i]-final)+(m<<(i-1));
}
