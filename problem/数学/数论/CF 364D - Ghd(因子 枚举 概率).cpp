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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 10;
ll gcd(ll a,ll b) { return b == 0?a:gcd(b,a%b);}
ll num[maxn],gval[maxn];
int cnt[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
        scanf("%I64d",&num[i]);
    ll ans = 1,limit;
    int m = (n + 1)/2,tot;
    for(int t = 0;t < 10;++t)
    {
        ll x = num[rand()*rand()%n];
        for(int i = 0;i < n;++i)
            gval[i] = gcd(num[i],x);
        sort(gval,gval + n);
        tot = 1;
        cnt[0] = 1;
        for(int i = 1;i < n;++i)
            if(gval[i] == gval[tot - 1])
                cnt[tot - 1]++;
            else
            {
                cnt[tot] = 1;
                gval[tot++] = gval[i];
            }
        limit = sqrt(x + 0.5);
        ll val,sum;
        for(ll i = 1;i*i <= x && x/i > ans;++i)
            if(x % i == 0)
            {
                val = x/i; sum = 0;
                for(int j = 0;j < tot;++j)
                    if(gval[j] % val == 0)
                        sum += cnt[j];
                if(sum >= m)
                    {ans = max(ans,val);break;}
                if(i <= ans) continue;
                val = i; sum = 0;
                for(int j = 0;j < tot;++j)
                    if(gval[j] % val == 0)
                        sum += cnt[j];
                if(sum >= m)
                    ans = max(ans,val);
            }
    }
    printf("%I64d\n",ans);
    return 0;
}
