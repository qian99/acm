#include<iostream>
using namespace std;
void main()
{
	int n,key;
	cin>>n;
	int a[100];
	for(int k=0;k<n;++k)
	{
		cin>>a[k];
	}
	for(int j=1;j<n;++j)
	{
		key=a[j];
		int i=j-1;
		while(i>=0&&a[i]>key)
		{
			a[i+1]=a[i];
			a[i]=key;
			i--;
		}
	}
	for(int m=0;m<n;m++)
	{
		cout<<a[m]<<" ";
	}
}