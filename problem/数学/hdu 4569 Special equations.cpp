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
ll a[10];
int n,pri;
ll cal(int x)
{
    ll sum=0;
    for(int i=0;i<n;++i)
    {
        sum+=a[i];
        sum*=x;
    }
    return sum+a[n];
}
int solve()
{
    for(int i=0;i<=pri;++i)
    {
        if(cal(i)%pri==0)
        {
            for(int j=i;j<=pri*pri;j+=pri)
            {
                if(cal(j)%(pri*pri)==0)
                    return j;
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    for(int tcase=1;tcase<=t;++tcase)
    {
        scanf("%d",&n);
        for(int i=0;i<=n;++i)
            scanf("%I64d",&a[i]);
        scanf("%d",&pri);
        int ans=solve();
        printf("Case #%d: ",tcase);
        if(ans==-1) puts("No solution!");
        else printf("%d\n",ans);
    }
    return 0;
}
