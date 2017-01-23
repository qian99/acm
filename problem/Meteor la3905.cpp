#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
using namespace std;
const double maxn=9999999999;
struct Event
{
	double t;
	int type;
};
Event meteor[200010];
void exchange(int x,int a,int w,double &L,double &R);
bool cmp(Event a,Event b);
int main()
{
	int tcase,w,h,n,x,y,t,a,b;
	scanf("%d",&tcase);
	while(tcase--)
	{
		scanf("%d%d%d",&w,&h,&n);
		int i,j=0;
		for(i=0;i<n;++i)
		{
			scanf("%d%d%d%d",&x,&y,&a,&b);
			double L=0;double R=maxn;
			exchange(x,a,w,L,R);
			exchange(y,b,h,L,R);
			if(R>L)
			{
				meteor[j].t=L;
				meteor[j++].type=0;
				meteor[j].t=R;
				meteor[j++].type=1;
			}
		}
		sort(meteor,meteor+j,cmp);
		int ans=0,c=0;
		for(i=0;i<j;++i)
		{
			if(meteor[i].type==0)
			{
				c++;
				if(c>ans)
				{
					ans=c;
				}
			}
			else
			{
				c--;
			}
		}
		printf("%d\n",ans);
	}
    return 0;  
}
void exchange(int x,int a,int w,double& L,double& R)
{
	double tl,tr;
	if(a==0)
	{
		if(x<=0||x>=w)
			R=L-1;
	}
	else if(a>0)
	{
		tl=-(double)x/a;
		tr=(double)(w-x)/a;
		if(tl>L)
			L=tl;
		if(tr<R)
			R=tr;
	}
	else
	{
		tl=(double)(w-x)/a;
		tr=-(double)x/a;
		if(tl>L)
			L=tl;
		if(tr<R)
			R=tr;
	}
}
bool cmp(Event a,Event b)
{
	if(a.t==b.t)
	{
		return a.type>b.type;
	}
	else
	{
		return a.t<b.t;
	}
}