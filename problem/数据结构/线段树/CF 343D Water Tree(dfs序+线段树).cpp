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
const int maxn=500000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge,Lv[maxn],Rv[maxn],pa[maxn],dfs_clock;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    Lv[u]=++dfs_clock;
    pa[u]=fa;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(edges[k].v==fa) continue;
        dfs(edges[k].v,u);
    }
    Rv[u]=dfs_clock;
}
int sum[maxn<<2],setv[maxn<<2];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int l,int r,int rt)
{
    if(setv[rt]!=-1)
    {
        int m=(l+r)>>1;
        setv[rt<<1]=setv[rt<<1|1]=setv[rt];
        sum[rt<<1]=(m-l+1)*setv[rt];
        sum[rt<<1|1]=(r-m)*setv[rt];
        setv[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    sum[rt]=0;setv[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        setv[rt]=v;
        sum[rt]=(r-l+1)*v;
        return;
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
        return sum[rt];
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    int res=0;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=0;
    scanf("%d",&n);
    int u,v;
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    dfs(1,-1);
    build(1,n,1);
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d",&u,&v);
        if(u==1)
        {
            int tmp=Query(Lv[v],Rv[v],1,n,1);
            Update(Lv[v],Rv[v],1,n,1,1);
            if(tmp!=Rv[v]-Lv[v]+1&&pa[v]!=-1)
                Update(Lv[pa[v]],Lv[pa[v]],1,n,1,0);
        }
        else if(u==2) Update(Lv[v],Lv[v],1,n,1,0);
        else
        {
            u=Query(Lv[v],Rv[v],1,n,1);
            if(u==Rv[v]-Lv[v]+1)
                puts("1");
            else puts("0");
        }
    }
    return 0;
}
