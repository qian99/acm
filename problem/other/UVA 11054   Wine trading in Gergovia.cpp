#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
ll num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
            scanf("%lld",&num[i]);
        ll sum=0;
        for(int i=0;i<n;++i)
        {
            if(num[i]>0)
            {
                sum+=num[i];
                num[i+1]+=num[i];
            }
            else if(num[i]<0)
            {
                sum-=num[i];
                num[i+1]+=num[i];
            }
        }
        printf("%lld\n",sum);
    }
    return 0;
}

