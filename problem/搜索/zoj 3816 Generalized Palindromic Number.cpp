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
int num[20],a[20],len;
ll pw[20],N,ans;
bool check(ll n)
{
    int tot = 0;
    while(n)
    {
        a[tot++] = n % 10;
        n /= 10;
    }
    unique(a,a + tot);
    for(int i = 0;i < tot/2;++i)
        if(a[i] != a[tot - i -1])
            return false;
    return true;
}
void dfs(int pos,int sp,ll now,int limit)
{
    if(now > N) return ;
    if(pos == sp)
    {
        ll tmp;
        for(int i = 9;i >= 0;--i)
        {
            tmp = now + pw[pos]*i;
            if(tmp <= N && tmp > ans)
            {
                ans = tmp;
                break;
            }
        }
        return ;
    }
    if(pos < sp)
    {
        ans = max(ans,now);
        return ;
    }
    int mx = limit ? num[pos] : 9;
    ll val;
    for(int i = mx ;i >= 0;--i)
    {
        val = now + pw[pos]*i;
        if(val/pw[pos] < ans/pw[pos]) break;
        if(pos < len - 1 && i == a[pos + 1])
        {
            a[pos] = i;
            dfs(pos - 1,sp,val,limit && i == mx);
        }
        else
        {
            val += pw[sp]*i;
            a[pos] = a[sp] = i;
            dfs(pos - 1,sp + 1,val,limit && i == mx);
        }
    }
    if(sp > 0)
    {
        a[sp] = a[sp-1];
        dfs(pos,sp + 1,now + pw[sp]*a[sp - 1],limit);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    pw[0] = 1;
    for(int i = 1;i < 20;++i)
        pw[i] = pw[i - 1]*10LL;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        len = 0;
        ll n;
        scanf("%lld",&n);
        n--;
        N = n;
        while(n)
        {
            num[len++] = n % 10;
            n /= 10;
        }
        ans = 0;
        if(check(N - 1)) ans = N - 1;
        dfs(len - 1,0,0,1);
        printf("%lld\n",ans);
    }
    return 0;
}
