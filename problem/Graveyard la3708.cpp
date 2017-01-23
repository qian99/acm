#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
const double len=10000;
double minnum(double a,double b);
int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		double t,j,s,p,q,sum=0;
		j=1;
		s=j/n;
		t=n+m;
		for(int i=1;i<t;++i)
		{
			p=i/t;
			q=(i+1)/t;
			if(s>=p&&s<=q)
			{
				sum+=minnum(s-p,q-s);
				j++;
				s=j/n;
				if(j>=n)
				{break;}
			}
		}
		sum*=len;
		printf("%.4lf\n",sum);
	}
    return 0;  
}
double minnum(double a,double b)
{
	return a<b?a:b;
}