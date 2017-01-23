#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50000+10;
double C[maxn],a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%lf",&a[i]);
        C[0]=0;
        for(int i=1;i<n;++i)
            C[i]=C[i-1]+log((double)n-i)-log((double)i);
        double ans=0;
        for(int i=0;i<n;++i)
        {
            if(a[i]<0)
                ans-=exp(C[i]+log(-a[i])-(n-1)*log(2.0));
            else ans+=exp(C[i]+log(a[i])-(n-1)*log(2.0));
        }
        printf("Case #%d: %.3lf\n",tcase,ans);
    }
    return 0;
}
