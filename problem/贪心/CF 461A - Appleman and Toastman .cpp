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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500500+10;
ll a[maxn],sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
        scanf("%I64d",&a[i]);
    sort(a,a+n);
    sum[0] = 2;
    for(int i = 1;i < n;++i)
        sum[i] = sum[i-1] + 1;
    sum[n-1]--;
    ll ans = 0;
    for(int i =0;i < n;++i)
        ans += a[i]*sum[i];
    printf("%I64d\n",ans);
    return 0;
}