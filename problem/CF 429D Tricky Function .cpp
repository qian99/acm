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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
ll a[maxn],sum[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%I64d",&a[i]);
    sum[0]=0;
    for(int i=1;i<=n;++i)
        sum[i]=sum[i-1]+a[i];
    ll ans=Inf,tmp;
    for(ll d=1;d<=n;++d)
    {
        if(d*d>ans) break;
        for(int j=d+1;j<=n;++j)
        {
            tmp=d*d+(sum[j]-sum[j-d])*(sum[j]-sum[j-d]);
            if(tmp<ans) ans=tmp;
        }
    }
    printf("%I64d\n",ans);
    return 0;
}
