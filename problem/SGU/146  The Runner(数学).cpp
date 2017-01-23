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
const ll p=10000;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double L;
    ll T,V,sum=0;
    int n;
    ll m;
    scanf("%lf",&L);
    scanf("%d",&n);
    m=(ll)(L*p+0.5);
    for(int i=0;i<n;++i)
    {
        scanf("%lld%lld",&T,&V);
        sum+=(T*V*p);
        sum%=m;
    }
    double ans=(double)sum/p;
    ans=min(ans,L-ans);
    printf("%.4lf\n",ans);
    return 0;
}
