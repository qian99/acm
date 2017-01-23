#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int val[maxn],id[maxn],to[maxn],d[maxn],addv[maxn<<2][2],type[maxn];
int head[maxn],nEdge,dfs_clock;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nn){v=vv;next=nn;}
}edges[maxn<<1];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(d,0,sizeof(d));
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=0;
}
int dfs(int u,int fa)
{
    id[u]=to[u]=++dfs_clock;
    int tmp;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;
        tmp=dfs(v,u);
        to[u]=max(to[u],tmp);
    }
    return to[u];
}
void build(int l,int r,int rt)
{
    addv[rt][0]=addv[rt][1]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void PushDown(int rt)
{
    if(addv[rt][0])
    {
        addv[rt<<1][0]+=addv[rt][0];
        addv[rt<<1|1][0]+=addv[rt][0];
        addv[rt][0]=0;
    }
    if(addv[rt][1])
    {
        addv[rt<<1][1]+=addv[rt][1];
        addv[rt<<1|1][1]+=addv[rt][1];
        addv[rt][1]=0;
    }
}
int Query(int p,int l,int r,int rt)
{
    if(l==r)
    {
        return addv[rt][type[l]];
    }
    int m=(l+r)>>1;
    PushDown(rt);
    if(m>=p) return Query(p,l,m,rt<<1);
    else return Query(p,m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        addv[rt][0]+=v;
        addv[rt][1]-=v;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        for(int i=1;i<=n;++i)
            type[id[i]]=(d[i]%2);
        build(1,n,1);
        int tmp,ans;
        while(m--)
        {
            scanf("%d",&tmp);
            if(tmp==1)
            {
                scanf("%d%d",&u,&v);
                if(type[id[u]]==1) v=-v;
                Update(id[u],to[u],1,n,1,v);
            }
            else
            {
                scanf("%d",&u);
                ans=val[u]+Query(id[u],1,n,1);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}

