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
const int maxn = 100000 + 10;
int b[maxn],p[maxn],n,m,tot;
ll sum[maxn];
bool check(int k,ll & cost)
{
    cost = 0;
    if(k == 0) return true;
    if(k > m) return false;
    ll val = 0,acost = 0;
    for(int i = 1;i <= k;++i)
    {
        //n - i + 1;
        //k - i + 1;
        if(b[n - i + 1] >= p[k - i + 1])
        {
            val += p[k - i + 1];
        }
        else
        {
            val += b[n - i + 1];
            acost += p[k - i + 1] - b[n - i + 1];
        }
    }
    if(acost > tot) return false;
    acost = tot - acost;
    if(tot >= sum[k])
        cost = 0;
    else
        cost = val - acost;
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&tot);
    for(int i = 1;i <= n;++i)
        scanf("%d",&b[i]);
    for(int i = 1;i <= m;++i)
        scanf("%d",&p[i]);
    sort(b + 1,b + n + 1);
    sort(p + 1,p + m + 1);
    sum[0] = 0;
    for(int i = 1;i <= m;++i)
        sum[i] = sum[i-1] + p[i];
    int L = 0,R = n + 1,mid;
    ll cost;
    while(R - L > 1)
    {
        mid = (L + R)>>1;
        if(check(mid,cost))
            L = mid;
        else
            R = mid;
    }
    check(L,cost);
    printf("%d %I64d\n",L,cost);
    return 0;
}