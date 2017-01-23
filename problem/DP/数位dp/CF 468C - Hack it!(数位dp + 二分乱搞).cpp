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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100+10;
ll dp[maxn],cnt[maxn];
int num[maxn];
ll f(int pos,bool limit,ll & tot)
{
    if(pos == -1) {tot = 1; return 0;}
    if(!limit && dp[pos] != -1) {tot = cnt[pos];return dp[pos];}
    int last = limit ? num[pos] : 9;
    ll ans = 0,tmp,tnt;
    tot = 0;
    for(int i = 0;i <= last ;++i)
    {
        tmp = f(pos - 1,limit && i == last,tnt);
        ans += i*tnt + tmp;
        tot += tnt;
    }
    if(!limit)
    {
        dp[pos] = ans;
        cnt[pos] = tot;
    }
    return ans;
}
ll cal(ll n)
{
    int len = 0;
    while(n)
    {
        num[len++] = n%10;
        n /= 10;
    }
    ll tmp;
    return f(len - 1,true,tmp);
}
ll c2(ll n)
{
    ll sum = 0;
    while(n)
    {
        sum += n%10;
        n /= 10;
    }
    return sum;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    ll n;
    cin>>n;
    ll L,R = 1e17,Rval,Lval;
    Rval = cal(R);
    ll l = 0,r = 1e17 + 1LL,mid;
    while(r - l > 1)
    {
        mid = (l + r)>>1;
        if(Rval - cal(mid) >= n)
            l = mid;
        else
            r = mid;
    }
    L = l;
    Lval = cal(L);
    while(Rval - Lval != n)
    {
        while(Rval - Lval < n) Rval += c2(++R);
        while(Rval - Lval > n) Lval += c2(++L);
    }
    cout<<(L+1)<<" "<<R<<endl;
    return 0;
}
