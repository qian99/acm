#include<iostream>
using namespace std;
int parents[1000];
int sum=0;
int Find(int x)
{
   return parents[x]!=x?parents[x]=Find(parents[x]):x;
}
void Uion(int a,int b)
{
 int x=Find(a);
 int y=Find(b);
 if(x!=y)
 {
  parents[x]=y;
  sum++;
 }
}
int main()
{
 int n,m;
 while(cin>>n,n)
 {
  cin>>m;
  for(int i=1;i<=n;++i)
  {
   parents[i]=i;
  }
  int x,y;
  sum=0;
  for(int j=0;j<m;++j)
  {
   cin>>x>>y;
   Uion(x,y);
  }
  cout<<n-sum-1<<endl;
 }
 return 0;
}