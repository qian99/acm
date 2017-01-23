#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
using namespace std;
const double pi=acos(-1.0);
const double d=0.00001;
double pie[10005];
int n,f;
bool canf(double area);
int main()
{
	int t,r;
	scanf("%d",&t);
	while(t--)
	{
		double maxa=0;
		scanf("%d%d",&n,&f);
		for(int i=0;i<n;++i)
		{
			scanf("%d",&r);
			pie[i]=r*r*pi;
			if(pie[i]>maxa)
			{
				maxa=pie[i];
			}
		}
		double ans=0;
		double mcase=maxa;
		while(mcase-ans>d)
		{
			double tp=(ans+mcase)/2;
			if(canf(tp))
			{
				ans=tp;
			}
			else
			{
				mcase=tp;
			}
		}
		printf("%.4lf\n",ans);
	}
    return 0;  
}
bool canf(double area)
{
	int sum=0;
	for(int i=0;i<n;++i)
	{
		sum+=(int)(pie[i]/area);
	}
	return sum>=f+1;
}