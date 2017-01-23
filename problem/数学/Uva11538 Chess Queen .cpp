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
//const int maxn=100+10;

int main()
{
    long long n,m;
    while(cin>>n>>m)
    {
        if(n==0&&m==0) break;
        if(n>m) swap(n,m);
        long long  res=n*m*(n-1)+n*m*(m-1)+2*n*(n-1)*(3*m-n-1)/3;
        cout<<res<<endl;
    }
    return 0;
}
