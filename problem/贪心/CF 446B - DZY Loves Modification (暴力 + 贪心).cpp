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
const int maxn = 1000 + 10;
const int maxm = 1000000+10;
int a[maxn][maxn];
ll rows[maxm],cols[maxm];
priority_queue<ll>q;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,k,p;
    scanf("%d%d%d%d",&n,&m,&k,&p);
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= m;++j)
            scanf("%d",&a[i][j]);
    rows[0] = cols[0] = 0;
    ll sum = 0;
    for(int i = 1;i <= n;++i)
    {
        sum = 0;
        for(int j = 1;j <= m;++j)
            sum += a[i][j];
        q.push(sum);
    }
    ll val;
    for(int i = 1;i <= k;++i)
    {
        val = q.top();q.pop();
        rows[i] = rows[i-1] + val;
        val -= m * p;
        q.push(val);
    }
    while(!q.empty()) q.pop();

    for(int i = 1;i <= m;++i)
    {
        sum = 0;
        for(int j = 1;j <= n;++j)
            sum += a[j][i];
        q.push(sum);
    }
    for(int i = 1;i <= k;++i)
    {
        val = q.top();q.pop();
        cols[i] = cols[i-1] + val;
        val -= p * n;
        q.push(val);
    }
    ll ans = rows[k];
    for(int i = 0;i < k;++i)
    {
        val = rows[i] + cols[k - i] - (ll)i*(k-i)*p;
        ans = max(ans,val);
    }
    printf("%I64d\n",ans);
    return 0;
}
