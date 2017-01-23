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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
int n,d,r;
int a[maxn],b[maxn];
int solve()
{
    int sum=0;
    for(int i=1;i<=n;++i)
        sum+=max(0,a[i]+b[n-i+1]-d);
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&d,&r))
    {
        if(n==0&&d==0&&r==0) break;
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&b[i]);
        sort(a+1,a+n+1);
        sort(b+1,b+n+1);
        int ans=solve()*r;
        printf("%d\n",ans);
    }
    return 0;
}
