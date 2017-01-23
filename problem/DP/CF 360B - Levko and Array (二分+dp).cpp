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
const int maxn=2000+10;
int dp[maxn],n,k;
int a[maxn];
bool check(int d)
{
    int x,y,z;
    for(int i=1;i<=n;++i)
    {
        dp[i]=i-1;
        for(int j=1;j<i;++j)
        {
            if((i-j-1)>=dp[i]) break;
            x=a[j];y=a[i];
            if(x>y) {z=x;x=y;y=z;}
            if(x+(ll)(i-j)*d<y) continue;
            if(dp[j]+(i-j-1)<dp[i]) dp[i]=dp[j]+(i-j-1);
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(dp[i]+(n-i)<=k) return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&k);
    ll L=0,R=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(i>1) R=max(R,(ll)abs(a[i]-a[i-1]));
    }
    while(L<R)
    {
        int m=(L+R)>>1;
        if(check(m)) R=m;
        else L=m+1;
    }
    printf("%I64d\n",L);
    return 0;
}
