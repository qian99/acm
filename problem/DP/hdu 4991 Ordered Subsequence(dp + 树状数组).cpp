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
const int maxn = 10000 + 10;
const int maxm = 100 + 10;
const int mod = 123456789;
struct BIT
{
    ll sum[maxn];
    int n;
    void Init(int n)
    {
        this->n = n;
        memset(sum,0,sizeof(sum));
    }
    void add(int x,ll v)
    {
        for(;x <= n;x += x&-x)
        {
            sum[x] += v;
            if(sum[x] >= mod) sum[x] -= mod;
        }
    }
    ll query(int x)
    {
        ll res = 0;
        for(;x > 0; x -= x&-x)
        {
            res += sum[x];
            if(res >= mod) res -= mod;
        }
        return res;
    }
}tree[maxm];
int a[maxn],b[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&a[i]);
            b[i] = a[i];
        }
        sort(b + 1,b + n + 1);
        int N = unique(b + 1,b + n + 1) - (b+1);
        for(int i = 1;i <= n;++i)
            a[i] = lower_bound(b + 1,b + N + 1,a[i]) - b;
        for(int i = 1;i <= m;++i)
            tree[i].Init(n);
        ll ans = 0,tmp;
        for(int i = 1;i <= n;++i)
        {
            for(int j = 2;j <= m;++j)
            {
                tmp = tree[j-1].query(a[i] - 1);
                tree[j].add(a[i],tmp);
            }
            tree[1].add(a[i],1);
            ans += tree[m].query(a[i]) - tree[m].query(a[i]-1);
            ans = (ans%mod + mod)%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

