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
const int maxn = 500000 + 10;
ll sum[maxn],a[maxn];
map<ll,int>mp;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        scanf("%I64d",&a[i]);
    sum[0] = 0;
    for(int i = 1;i <= n;++i)
    {
        sum[i] = sum[i-1] + a[i];
        if(i != n)
            mp[sum[i]]++;
    }
//    cout<<mp[0]<<endl;
    ll ans = 0,val;
    for(int i = 1;i < n - 1;++i)
    {
        val = sum[i];
        mp[val]--;
//        cout<<mp[0]<<endl;
        if(sum[n] - val == val + val)
        {
            ans += mp[val + val];
        }
    }
    printf("%I64d\n",ans);
    return 0;
}