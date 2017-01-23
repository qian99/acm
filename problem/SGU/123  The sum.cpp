#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll f[50],sum[50];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    f[1]=f[2]=1;
    for(int i=2;i<41;++i)
      f[i]=f[i-1]+f[i-2];
    sum[0]=0;
    for(int i=1;i<41;++i)
      sum[i]+=sum[i-1]+f[i];
    int n;
    while(cin>>n)
    {
        cout<<sum[n]<<endl;
    }
    return 0;
}
