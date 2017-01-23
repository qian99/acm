#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=10000+10;
int pp[maxn],dd[maxn];
bool f(int l,int r,int v)
{
    while(l<r)
    {
        int m=(l+r)/2;
        if(pp[m]<v)
        {
            l=m+1;
        }
        else if(pp[m]>v)
        {
            r=m;
        }
        else
        {
            return true;
        }
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=1;i<=10000;++i)
      pp[i]=i*i;
    dd[0]=0;
    for(int i=3;i<=10000;++i)
    {
        dd[i]=dd[i-1];
        //bool flag=false;
        for(int j=i-1;j>=2;--j)
        {
            int r=pp[i]-pp[j];
            if(f(1,j,r)) dd[i]++;
            if(pp[j]+pp[j-1]<pp[i]) break;
        }
    }
    int n;
    while(cin>>n)
    {
        cout<<dd[n]<<endl;
    }
    return 0;
}