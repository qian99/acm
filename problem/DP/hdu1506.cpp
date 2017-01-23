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
const int maxn=100000+10;
int lf[maxn],rn[maxn],num[maxn];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        lf[1]=1;
        rn[n]=n;
        for(int i=2;i<=n;++i)
        {
            int t=i;
            while(t>1&&num[i]<=num[t-1]) t=lf[t-1];
            lf[i]=t;
        }
        for(int i=n-1;i>=1;--i)
        {
            int t=i;
            while(t<n&&num[i]<=num[t+1]) t=rn[t+1];
            rn[i]=t;
        }
        __int64 maxret=0,ret;
        for(int i=1;i<=n;++i)
        {
            ret=(__int64)(rn[i]-lf[i]+1)*num[i];
            maxret=max(maxret,ret);
        }
        printf("%I64d\n",maxret);
    }
    return 0;
}
