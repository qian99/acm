#include<iostream>
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
const int maxn=100000+10;
ll minv[maxn<<2];
struct Node
{
    int val,id;
    bool operator <(const Node &a) const
    {
        return val<a.val;
    }
}node[maxn];
int val[maxn],cov[maxn],qs[maxn],maxpre[maxn];
inline void PushUp(int rt)
{
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    minv[rt]=Inf;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,ll v)
{
    if(l==r)
    {
        minv[rt]=v;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return minv[rt];
    int m=(l+r)>>1;
    ll res=Inf;
    if(m>=L) res=min(res,Query(L,R,l,m,rt<<1));
    if(m<R) res=min(res,Query(L,R,m+1,r,rt<<1|1));
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&node[i].val);
            node[i].id=i;
        }
        sort(node+1,node+n+1);
        for(int i=1;i<=n;++i) cov[node[i].id]=i;
        int u,v;
        memset(maxpre,0xff,sizeof(maxpre));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            u=cov[u];v=cov[v];
            if(u>v) swap(u,v);
            maxpre[v]=max(maxpre[v],u);
        }
        node[n+1].val=node[n].val;
        build(0,n,1);
        Update(0,0,n,1,0);
        ll dp=0;
        int mp=0;
        for(int i=1;i<=n;++i)
        {
            if(maxpre[i]!=-1) mp=max(mp,maxpre[i]);
            dp=Query(mp,i-1,0,n,1);
            Update(i,0,n,1,dp+node[i+1].val-node[i].val);
        }
        printf("%lld\n",dp);
    }
    return 0;
}
