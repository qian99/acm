#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
struct Ant
{
	int firstnum,pos,state;
};
Ant before[10005],after[10005];
bool cmp1(Ant a,Ant b);
bool cmp2(Ant a,Ant b);
int main()
{
	int i,l,t,n,casenum,k;
	char tc;
	scanf("%d",&casenum);
	k=1;
	while(casenum--)
	{
		scanf("%d%d%d",&l,&t,&n);
		for(i=0;i<n;++i)
		{
			scanf("%d %c",&before[i].pos,&tc);
			before[i].firstnum=i+1;
			before[i].state=(tc=='L')?-1:1;
			after[i].firstnum=i+1;
			after[i].state=before[i].state;
			after[i].pos=(after[i].state==1)?(before[i].pos+t):(before[i].pos-t);
		}
		sort(before,before+n,cmp1);
		sort(after,after+n,cmp1);
		for(i=0;i<n;++i)
		{
			if(after[i].pos==after[i+1].pos)
			{
				before[i].state=0;
				before[i].pos=after[i].pos;
				i++;
				before[i].state=0;
			}
			else
			{
				before[i].state=after[i].state;
			}
			before[i].pos=after[i].pos;
		}
		sort(before,before+n,cmp2);
		printf("Case #%d:\n",k);
		k++;
		for(i=0;i<n;++i)
		{
			if(before[i].pos<0||before[i].pos>l)
			{
				printf("Fell off\n");
			}
			else if(before[i].state==0)
			{
				printf("%d Turning\n",before[i].pos);
			}
			else if(before[i].state==1)
			{
				printf("%d R\n",before[i].pos);
			}
			else
			{
				printf("%d L\n",before[i].pos);
			}
		}
		printf("\n");
	}
    return 0;  
}
bool cmp1(Ant a,Ant b)
{
	return a.pos<b.pos;
}
bool cmp2(Ant a,Ant b)
{
	return a.firstnum<b.firstnum;
}