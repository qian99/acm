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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000+10;
ll a[maxn],sum[maxn];
int n,m,w;
bool check(ll mid)
{
    memset(sum,0,sizeof(sum));
    ll add = 0,need = 0;
    for(int i = 1;i <= n;++i)
    {
        add += sum[i];
        if(a[i] + add < mid)
        {
            need += mid - a[i] - add;
            if(i + w <= n) sum[i+w] -= mid - a[i] - add;
            add += mid - a[i] - add;
        }
    }
    return m >= need;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&w);
    for(int i = 1;i <= n;++i)
        scanf("%I64d",&a[i]);
    ll L = 0 ,R = 1e10;
    while(R - L > 1)
    {
        ll mid = (L + R)>>1;
        if(check(mid)) L = mid;
        else R = mid;
    }
    printf("%I64d\n",L);
    return 0;
}