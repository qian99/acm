#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<assert.h>
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
const int maxn = 200000 + 10;
const int mod = 1e9 + 7;
int P[maxn];
char str[maxn];
struct SegTree
{
    ll sum[maxn<<2],val[maxn<<2][2];
    int cnt[maxn<<2],type;
    void PushUp(int rt)
    {
        cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
        val[rt][0] = val[rt<<1][0] + val[rt<<1|1][0] + sum[rt<<1]*cnt[rt<<1|1]*2%mod;
        val[rt][1] = val[rt<<1][1] + val[rt<<1|1][1] + sum[rt<<1]*cnt[rt<<1|1]*2%mod;
        if(sum[rt] >= mod) sum[rt] -= mod;
        val[rt][0] %= mod;
        val[rt][1] %= mod;
    }
    void build(int l,int r,int rt)
    {
        if(l == r)
        {
            cnt[rt] = sum[rt] = 0;
            val[rt][0] = val[rt][1] = 0;
            if((l & 1) == type)
            {
                cnt[rt] = 1;
                sum[rt] = P[l];
                val[rt][0] = P[l]*2;
                val[rt][1] = P[l];
            }
            return ;
        }
        int m = (l + r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(rt);
    }
    void Update(int p,int l,int r,int rt,int v)
    {
        if(l == r)
        {
            sum[rt] = v;
            val[rt][0] = v*2;
            val[rt][1] = v;
            return ;
        }
        int m = (l + r)>>1;
        if(m >= p) Update(p,l,m,rt<<1,v);
        else Update(p,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
    ll Query(int L,int R,int l,int r,int rt,int & size,ll & sval)
    {
        if(l >= L && r <= R)
        {
            size = cnt[rt];
            sval = sum[rt];
            return val[rt][type&1];
        }
        int m = (l + r)>>1;
        if(m >= R) return Query(L,R,l,m,rt<<1,size,sval);
        else if(m < L) return Query(L,R,m+1,r,rt<<1|1,size,sval);
        else
        {
            ll r1,r2,sv1,sv2;
            int s1,s2;
            r1 = Query(L,R,l,m,rt<<1,s1,sv1);
            r2 = Query(L,R,m+1,r,rt<<1|1,s2,sv2);
            size = s1 + s2;
            sval = sv1 + sv2;
            if(sval >= mod) sval -= mod;
            return (r1 + r2 + sv1*s2*2)%mod;
        }
    }
}tree[2];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int n = strlen(str);
        for(int i = 1;i <= n;++i)
            P[i] = P[i + n] = str[i - 1] - '0';
        n *= 2;
        tree[0].type = 0;
        tree[0].build(1,n,1);
        tree[1].type = 1;
        tree[1].build(1,n,1);
        int q,x,d,type;
        ll l,r,ans,svtmp;
        int L,R,stmp,p;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&type);
            if(type == 1)
            {
                scanf("%d%d",&x,&d);
                tree[x&1].Update(x,1,n,1,d);
                tree[(x+n/2)&1].Update(x + n/2,1,n,1,d);
            }
            else
            {
                scanf("%lld%lld",&l,&r);
                ll lblock = (l-1)/n,rblock = (r-1)/n,m;
                int k;
                if((r-l+1)&1) k = 1;
                else k = 2;
                tree[l&1].type = k;
                if(lblock == rblock)
                {
                    L = l % n;
                    R = r % n;
                    if(L == 0) L = n;
                    if(R == 0) R = n;
                    ans = tree[l&1].Query(L,R,1,n,1,stmp,svtmp);
                }
                else
                {
                    L = l % n;
                    R = r % n;
                    if(R == 0) R = n;
                    if(L == 0) L = n;
                    p = l&1;
                    ans = tree[p].Query(1,R,1,n,1,stmp,svtmp);
                    m = rblock - lblock - 1;
                    m %= mod;
                    if(m)
                    {
                        ans += m*tree[p].val[1][k&1]%mod
                            +  stmp*tree[p].sum[1]%mod*m*2%mod
                            +  m*(m-1)/2%mod*tree[p].sum[1]%mod*tree[p].cnt[1]*2%mod;
                    }
                    ans %= mod;
                    m = m*tree[p].cnt[1]%mod + stmp;
                    ll tmp = tree[p].Query(L,n,1,n,1,stmp,svtmp);
                    ans += tmp + m * svtmp*2;
                }
                ans = (ans%mod + mod)%mod;
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
