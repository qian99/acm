#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define eps 1e-9
using namespace std;
const int maxn=10000+10;
double x[maxn],y[maxn];
int main()
{
	int n;
	double ax=0,ay=0;
	int wh=0,i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		scanf("%lf%lf",&x[i],&y[i]);
		ax+=(wh?-1:1)*x[i];
		ay+=(wh?-1:1)*y[i];
		wh^=1;
	}
	if(!(n&1))
	{
		if(abs(ax)<eps&&abs(ay)<eps)
		{
			ax=ay=1;
		}
		else
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	printf("%.3lf %.3lf\n",ax,ay);
	for(i=1;i<n;++i)
	{
		ax=2*x[i]-ax;
		ay=2*y[i]-ay;
		printf("%.3lf %.3lf\n",ax,ay);
	}
	return 0;
}
