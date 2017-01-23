#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
const int MaxNum=1000010;
long long village[MaxNum],c[MaxNum];
int main()
{
	int n,i,j;
	long long sum,m;
	while(~scanf("%d",&n))
	{
		sum=0;
		for(i=1;i<=n;++i)
		{
			scanf("%lld",&village[i]);
			sum+=village[i];
		}
		m=sum/n;
		c[0]=0;
		for(i=1;i<n;++i)
		{
			c[i]=c[i-1]+village[i]-m;
		}
		sort(c,c+n);
		long long t=c[n/2];
		long long ans=0;
		for(i=0;i<n;++i)
		{
			ans+=(t-c[i])>0?(t-c[i]):(c[i]-t);
		}
		printf("%lld\n",ans);
	}
    return 0;  
}