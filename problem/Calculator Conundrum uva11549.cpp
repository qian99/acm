#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
using namespace std;
int next(int n,int m);
int main()
{
	int t,n,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		int m1,m2,ans;
		ans=k;
		m1=m2=k;
		do
		{
			m1=next(n,m1);
			m2=next(n,m2);
			if(m2>ans)
			{
				ans=m2;
			}
			m2=next(n,m2);
			if(m2>ans)
			{
				ans=m2;
			}

		}
		while(m1!=m2);
		printf("%d\n",ans);
	}
    return 0;  
}
int next(int n,int m)
{
	if(m==0)
		return 0;
	long long  num=m;
	num*=num;
	int res=0;
	int a[20];
	int i=0;
	while(num!=0)
	{
		a[i]=num%10;
		num/=10;
		i++;
	}
	if(n>i)
	{
		n=i;
	}
	for(int j=0;j<n;++j)
	{
		res=res*10+a[i-j-1];
	}
	return res;
}
