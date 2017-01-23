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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll Nm[13];
ll pw[13];
int num[10];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Nm[0]=1;
    pw[0]=1;
    for(int i=1;i<=12;++i)
    {
        Nm[i]=Nm[i-1]*i;
        pw[i]=pw[i-1]*10;
    }
    int n,m;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(num,0,sizeof(num));
        for(int i=0;i<n;++i)
        {
            scanf("%d",&m);
            num[m]++;
        }
        ll ans=0;
        ll sum=Nm[n];
        for(int i=0;i<10;++i)
           sum/=Nm[num[i]];
        for(int i=1;i<=n;++i)
        {
           for(int j=0;j<10;++j)
             ans+=(num[j]*sum/n)*j*pw[i-1];
        }
        cout<<(unsigned long long)ans<<endl;
    }
    return 0;
}
