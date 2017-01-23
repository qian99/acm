#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=300000+10;
const int mod=1000000000+7;
struct SegTree
{
    ll sum[maxn<<2],addv[maxn<<2];
    void PushUp(int rt)
    {
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }
    void PushDown(int l,int r,int rt)
    {
        if(addv[rt])
        {
            int m=(l+r)>>1;
            addv[rt<<1]=(addv[rt<<1]+addv[rt])%mod;
            addv[rt<<1|1]=(addv[rt<<1|1]+addv[rt])%mod;
            sum[rt<<1]=(sum[rt<<1]+(m-l+1)*addv[rt])%mod;
            sum[rt<<1|1]=(sum[rt<<1|1]+(r-m)*addv[rt])%mod;
            addv[rt]=0;
        }
    }
    void build(int l,int r,int rt)
    {
        sum[rt]=addv[rt]=0;
        if(l==r) return ;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    ll Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R)
            return sum[rt];
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        ll sum=0;
        if(m>=L) sum+=Query(L,R,l,m,rt<<1);
        if(m<R) sum+=Query(L,R,m+1,r,rt<<1|1);
        return sum%mod;
    }
    void Update(int L,int R,int l,int r,int rt,ll v)
    {
        if(l>=L&&r<=R)
        {
            addv[rt]=(addv[rt]+v)%mod;
            sum[rt]=(sum[rt]+(r-l+1)*v)%mod;
            return;
        }
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        if(m>=L) Update(L,R,l,m,rt<<1,v);
        if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
}t1,t2;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],d[maxn],l[maxn],r[maxn],nEdge,dfs_clock;
int n,q;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=0;
    d[1]=0;
    t1.build(1,n,1);
    t2.build(1,n,1);
}
void dfs(int u,int fa)
{
    l[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs(v,u);
    }
    r[u]=dfs_clock;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    Init();
    int type,v,x,k;
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&v);
        AddEdges(i,v);
    }
    dfs(1,-1);
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&type);
        if(type==1)
        {
            scanf("%d%d%d",&v,&x,&k);
            t1.Update(l[v],r[v],1,n,1,x+(ll)k*d[v]%mod);
            t2.Update(l[v],r[v],1,n,1,k);
        }
        else
        {
            scanf("%d",&v);
            ll ans=t1.Query(l[v],l[v],1,n,1);
            ans-=t2.Query(l[v],l[v],1,n,1)*d[v];
            ans=(ans%mod+mod)%mod;
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
