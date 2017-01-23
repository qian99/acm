#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
using namespace std;
int needs[100005];
int leftn[100005];
int rightn[100005];
int n;
bool canf(int p);
int main()
{
	while(~scanf("%d",&n))
	{
		if(n==0)
		{break;}
		int i;
		for(i=0;i<n;++i)
		{
			scanf("%d",&needs[i]);
		}
		needs[n]=needs[0];
		int ans=0,t=0;
		if(n%2==0)
		{
			for(i=0;i<n;++i)
			{
				if(needs[i]+needs[i+1]>ans)
				{
					ans=needs[i]+needs[i+1];
				}
			}
		}
		else
		{
			for(i=0;i<n;++i)
			{
				if(needs[i]>t)
				{
					t=needs[i];
				}
			}
			t*=3;
			while(ans<t)
			{
				int temp=ans+(t-ans)/2;
				if(canf(temp))
				{
					t=temp;
				}
				else
				{
					ans=temp+1;
				}
			}
		}
		printf("%d\n",ans);
	}
    return 0;  
}
bool canf(int p)
{
	int s,r=needs[0];
	leftn[0]=needs[0];
	rightn[0]=0;
	for(int i=1;i<n;++i)
	{
		if(i%2==0)
		{
			s=(p-r)-rightn[i-1];
			if(s>=needs[i])
			{
				rightn[i]=needs[i];
				leftn[i]=0;
			}
			else
			{
				rightn[i]=s;
				if((needs[i]-s)>(r-leftn[i-1]))
					return false;
				leftn[i]=needs[i]-s;
			}
		}
		else
		{
			s=r-leftn[i-1];
			if(s>=needs[i])
			{
				leftn[i]=needs[i];
				rightn[i]=0;
			}
			else
			{
				leftn[i]=s;
				if((needs[i]-s)>(p-r-rightn[i-1]))
					return false;
				rightn[i]=needs[i]-s;
			}
		}	
	}
	return leftn[n-1]==0;
}
