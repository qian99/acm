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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int mod=1000000007;
vector<int>G[maxn];
int Lv[maxn],Rv[maxn],dfs_clock;
ll id[maxn],val[maxn];
void dfs(int u,int fa)
{
    Lv[u]=++dfs_clock;
    int cnt=0;
    for(int i=0;i<(int)G[u].size();++i)
    {
        int v=G[u][i];
        if(v==fa) continue;
        id[v]=id[u]*(++cnt)%mod;
        dfs(v,u);
    }
    Rv[u]=dfs_clock;
}
ll pow_mod(ll x,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
inline ll inv(ll x)
{
    return pow_mod(x,mod-2);
}
inline void Addit(ll & val,ll x)
{
    val+=x;
    val=(val%mod+mod)%mod;
}
ll sum[maxn<<2],addv[maxn<<2],mul[maxn<<2];
void PushUp(int rt)
{
    sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%mod;
    mul[rt]=(mul[rt<<1]+mul[rt<<1|1])%mod;
}
void PushDown(int rt)
{
    if(addv[rt])
    {
        Addit(addv[rt<<1],addv[rt]);
        Addit(addv[rt<<1|1],addv[rt]);
        Addit(sum[rt<<1],addv[rt]*mul[rt<<1]%mod);
        Addit(sum[rt<<1|1],addv[rt]*mul[rt<<1|1]%mod);
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    sum[rt]=addv[rt]=0;
    if(l==r)
    {
        mul[rt]=val[l];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,ll v)
{
    if(l>=L&&r<=R)
    {
        Addit(addv[rt],v);
        Addit(sum[rt],v*mul[rt]%mod);
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return sum[rt];
    PushDown(rt);
    int m=(l+r)>>1;
    ll res=0;
    if(m>=L) Addit(res,Query(L,R,l,m,rt<<1));
    if(m<R) Addit(res,Query(L,R,m+1,r,rt<<1|1));
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n;++i) G[i].clear();
        dfs_clock=0;
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=1;i<=n;++i)
            sort(G[i].begin(),G[i].end());
        id[1]=1;
        dfs(1,-1);
        for(int i=1;i<=n;++i)
            val[Lv[i]]=id[i];
        build(1,n,1);
        int type;
        ll ans;
        while(m--)
        {
            scanf("%d%d",&type,&u);
            if(type==1)
            {
                scanf("%d",&v);
                v=v*inv(id[u])%mod;
                Update(Lv[u],Rv[u],1,n,1,v);
            }
            else if(type==2)
            {
                ans=Query(Lv[u],Rv[u],1,n,1);
                printf("%lld\n",ans);
            }
            else
            {
                ans=Query(Lv[u],Lv[u],1,n,1);
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
