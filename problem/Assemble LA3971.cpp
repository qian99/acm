#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
#include<cmath>
#include<vector>
using namespace std;
int n,b,cnt;
map <string,int> id;
int getID(string s);
struct Component
{
	int p;
	int q;
};
vector<Component>comp[1005];
bool canf(int nq);
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		char type[30],name[30];
		int tp,tq;
		scanf("%d%d",&n,&b);
		cnt=0;
		for(int i=0;i<n;++i)
		{
			comp[i].clear();
		}
		id.clear();
		int maxq=0;
		for(int j=0;j<n;++j)
		{
			scanf("%s%s%d%d",type,name,&tp,&tq);
			if(tq>maxq)
			{
				maxq=tq;
			}
			Component cm;
			cm.p=tp;
			cm.q=tq;
			comp[getID(type)].push_back(cm);
		}
		int ans=0;
		while(ans<maxq)
		{
			int m=ans+(maxq-ans+1)/2;
			if(canf(m))
			{
				ans=m;
			}
			else
			{
				maxq=m-1;
			}
		}
		printf("%d\n",ans);
	}
    return 0;  
}
int getID(string s)
{
	if(id.count(s)==0)
	{
		id[s]=cnt++;
	}
	return id[s];
}
bool canf(int nq)
{
	int sum=0;
	for(int i=0;i<cnt;++i)
	{
		int cheapest=b+1;
		int m=comp[i].size();
		for(int j=0;j<m;++j)
		{
			if(comp[i][j].q>=nq&&comp[i][j].p<cheapest)
			{
				cheapest=comp[i][j].p;
			}
		}
		if(cheapest==b+1)
			return false;
		sum+=cheapest;
		if(sum>b)
			return false;
	}
	return true;
}