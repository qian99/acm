#include<cstdio>   
#include<cstring>   
#include<algorithm>  
#include<iostream> 
#include<string>
#include<map>
using namespace std;
int f(int i);
int main()
{
	int n;
	while(scanf("%d",&n)==1)
	{
		printf("%d\n",f(n));
	}
    return 0;  
}
int f(int i)
{
	if(i==1)
	{
		return 1;
	}
	else
	{
		return f(i/2)+1;
	}
}
