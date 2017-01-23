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
const int maxn=10000000+10;
long long  a[maxn];

int main()
{
    long long n;
    a[3]=0;a[4]=1;
    for(int  i=5;i<=1000000;++i)
    {
        long long m=i/2-1;
        if(i%2!=0)
        {
            a[i]=a[i-1]+(1+m)*m;
        }
        else
        {
            m-=1;
            a[i]=a[i-1]+(m+1)*(m+1);
        }
    }
    while(cin>>n)
    {
        if(n<3) break;
        cout<<a[n]<<endl;
    }
    return 0;
}