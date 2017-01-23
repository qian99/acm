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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
ll sum[maxn],minp[maxn],mins[maxn];
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        sum[0]=0;
        for(int i=1;i<=n;++i)
            sum[i]=sum[i-1]+a[i];
        minp[1]=sum[1];
        for(int i=2;i<=n;++i)
            minp[i]=min(sum[i],minp[i-1]);
        mins[n]=sum[n];
        for(int i=n-1;i>=1;--i)
            mins[i]=min(sum[i],mins[i+1]);
        int cnt=0;
        ll x,y;
        if(minp[n]>=0) cnt++;
        for(int i=1;i<n;++i)
        {
            x=mins[i+1];
            y=minp[i];
            if(x-sum[i]>=0&&y+(sum[n]-sum[i])>=0) cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
