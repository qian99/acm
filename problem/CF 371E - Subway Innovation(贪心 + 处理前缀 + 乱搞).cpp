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
const int maxn = 300000+10;
ll sum[maxn];
pair<int,int>x[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,k,p;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&p);
        x[i].first = p;
        x[i].second = i;
    }
    sort(x+1,x+n+1);
    scanf("%d",&k);
    sum[0] = 0;
    for(int i = 1;i <= n;++i)
        sum[i] = sum[i-1] + x[i].first;
    ll minval = 0,ans;
    int s = 1,t = k;
    for(int i = 1;i <= k;++i)
        minval += (ll)i*x[i].first - sum[i];
    ans = minval;
    for(int i = 1;i + k <= n;++i)
    {
        minval -= sum[i + k - 1] - sum[i-1] - (ll)k*x[i].first;
        minval += (ll)k*x[i+k].first - (sum[i+k] - sum[i]);
        if(minval < ans)
        {
            ans = minval;
            s = i + 1;
            t = i + k;
        }
    }
    for(int i = s;i <= t;++i)
    {
        if(i > s) printf(" ");
        printf("%d",x[i].second);
    }
    printf("\n");
    return 0;
}
