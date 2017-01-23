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
const int maxn = 50000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],factor[maxn][33],pcnt,nEdge;
int sons[maxn],pa[maxn],q[maxn],flag[maxn];
ll ans,val[maxn],primes[33];
map<ll,int>mp;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
int findroot(int x)
{
    int tail = 0,u,v;
    q[tail++] = x;
    pa[x] = 0;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            pa[v] = u;
            q[tail++] = v;
        }
    }
    int minv = inf,root = -1,mx;
    for(int i = tail - 1;i >= 0;--i)
    {
        u = q[i];
        sons[u] = 1;
        mx = 0;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            sons[u] += sons[v];
            mx = max(mx,sons[v]);
        }
        mx = max(mx,tail - sons[u]);
        if(mx < minv)
        {
            minv = mx;
            root = u;
        }
    }
    return root;
}
inline ll getmsk(int u)
{
    ll res = 0;
    for(ll i = 0;i < pcnt;++i)
        res |= (ll)factor[u][i]<<(i<<1LL);
    return res;
}
inline ll Uion(ll x,ll y)
{
    ll res = 0;
    for(ll i = 0;i < pcnt;i++)
    {
        res |= ((
                 ((x>>(i<<1LL)) & 3) +
                 ((y>>(i<<1LL)) & 3)
                )%3)<<(i<<1LL);
    }
    return res;
}
inline ll getRev(ll x)
{
    ll res = 0;
    int v;
    for(ll i = 0;i < pcnt;++i)
    {
        v = (x>>(i<<1LL)) & 3;
        if(v == 1) res |= (2LL<<(i<<1));
        else if(v == 2) res |= (1LL<<(i<<1));
    }
    return res;
}
void cal(int x,int fa,ll fval)
{
    pa[x] = fa;
    int tail = 0,u,v;
    q[tail++] = x;
    val[fa] = 0;
    ll tmp;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        val[u] = Uion(val[pa[u]],getmsk(u));
        tmp = getRev(val[u]);
        if(mp.find(tmp) != mp.end())
            ans += mp[tmp];
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v == pa[u] || flag[v]) continue;
            pa[v] = u;
            q[tail++] = v;
        }
    }
    for(int i = tail - 1;i >= 0;--i)
    {
        u = q[i];
        tmp = Uion(val[u],fval);
        mp[tmp]++;
    }
}
void solve(int x)
{
    int root = findroot(x);
    flag[root] = 1;
    mp.clear();
    ll rmsk = getmsk(root);
    if(rmsk == 0) ans++;
    mp[rmsk] = 1;
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(flag[v]) continue;
        cal(v,root,rmsk);
    }
    for(int k = head[root];k != -1;k = edges[k].next)
        if(!flag[edges[k].v]) solve(edges[k].v);
}

int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        memset(flag,0,sizeof(flag));
        scanf("%d",&pcnt);
        for(int i = 0;i < pcnt;++i)
            scanf("%I64d",&primes[i]);
        ll num;
        for(int i = 1;i <= n;++i)
        {
            memset(factor[i],0,sizeof(factor[i]));
            scanf("%I64d",&num);
            for(int j = 0;j < pcnt;++j)
            {
                while(num % primes[j] == 0)
                {
                    factor[i][j]++;
                    num /= primes[j];
                }
                factor[i][j] %= 3;
            }
        }
        int u,v;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        ans = 0;
        solve(1);
        printf("%I64d\n",ans);
    }
    return 0;
}

