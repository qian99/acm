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
const int maxn=1000+10;
int num[maxn],sum[maxn];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
          scanf("%d",&num[i]);
        sum[0]=num[0];
        int ans=num[0];
        for(int i=1;i<n;++i)
        {
            int m=0;
            for(int j=i-1;j>=0;j--)
            {
                if(num[i]>num[j])
                   m=max(sum[j],m);
            }
            sum[i]=m+num[i];
            ans=max(ans,sum[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
