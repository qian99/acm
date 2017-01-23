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
const int maxn= 10000+10;
const ll MAXV = 1e12;
vector<ll>pw[maxn];
void Init()
{
    ll tmp;
    for(int i = 4;i < maxn ; ++i)
    {
        pw[i].push_back(1);
        for(int j = 1;j < maxn;++j)
        {
            tmp = pw[i][j-1]*i;
            if(tmp > MAXV) break;
            pw[i].push_back(tmp);
        }
    }
}
bool check(ll n,ll k)
{
    int len = 0,size = pw[k].size();
    for(int i = 0;i < size ; ++i)
        if(pw[k][i]*3 <= n) len = i;
        else break;
    bool flag;
    for(int i = len;i >= 0;--i)
    {
        flag = false;
        for(int j = min(6LL,k-1);j >= 3;--j)
        {
            if(j*pw[k][i] <= n)
            {
                n -= j*pw[k][i];
                flag = true;
                break;
            }
        }
        if(!flag) return false;
    }
    return n==0;
}
ll base[maxn];
int tot ;
void cal(ll a,ll b,ll c,ll n)
{
    if(a == 2)
    {
        if(n > c && ((n-c)%b==0))
        {
            base[tot++] = (n - c)/b;
        }
        return ;
    }
    c -= n;
    ll d = b*b - 4*a*c;
    ll tmp = sqrt(d + eps);
    if(tmp * tmp == d)
    {
        ll x = tmp - b;
        if(x % (2*a) == 0)
        {
            x /=(2*a);
            base[tot++] = x;
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        ll n;
        scanf("%I64d\n",&n);
        printf("Case #%d: ",++tcase);
        if(n == 3 || n == 4 || n == 5 || n == 6)
        {
            printf("-1\n");
            continue;
        }
        int ans = 0;
        for(int i = 4; i < maxn;++i)
            if(check(n,i)) ans ++;
        tot = 0;
        for(int i = 2;i <= 6;++i)
            for(int j = 3;j <= 6;++j)
                for(int k = 3;k <= 6;++k)
                    cal(i,j,k,n);
        sort(base , base + tot);
        tot = unique(base,base + tot) - base;
        for(int i = 0;i < tot ;++i)
            if(base[i] >= maxn) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
