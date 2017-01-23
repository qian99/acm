#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
struct comman
{
	int jt,wt;
};
comman a[1005];
bool cmp(comman a,comman b);
int main()
{
	int n,t;
	t=1;
	while(~scanf("%d",&n))
	{
		if(n==0)
		{break;}
		for(int i=0;i<n;++i)
		{
			scanf("%d%d",&a[i].jt,&a[i].wt);
		}
		sort(a,a+n,cmp);
		int nowtime=0;
		int maxtime=0;
		for(int j=0;j<n;++j)
		{
			nowtime+=a[j].jt;
			if(maxtime<nowtime+a[j].wt)
			{
				maxtime=nowtime+a[j].wt;
			}
		}
		printf("Case %d: %d\n",t,maxtime);
		t++;
	}
    return 0;  
} 
bool cmp(comman a,comman b)
{
	return a.wt>b.wt;
}