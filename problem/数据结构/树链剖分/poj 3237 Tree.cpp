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
const int maxn=10000+10;
struct Edge
{
    int u,v,w,next;
    Edge(){};
    Edge(int uu,int vv,int ww,int nx){u=uu;v=vv;w=ww;next=nx;}
}edges[maxn<<1];
int head[maxn],d[maxn],nEdge,N;
int pa[maxn],ft[maxn],childs[maxn],id[maxn<<1],val[maxn];
bool flag[maxn<<1];
void AddEdge(int u,int v,int w)
{
    edges[++nEdge]=Edge(u,v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(v,u,w,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(ft,0xff,sizeof(ft));
    memset(flag,0,sizeof(flag));
    memset(d,0,sizeof(d));
    nEdge=-1;N=0;
}
int dfs(int u,int fa)
{
    childs[u]=0;
    int cnt=1,mx=-1,p;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        childs[u]++;d[v]=d[u]+1;
        pa[v]=k;
        int ct=dfs(v,u);
        if(ct>mx) {mx=ct;p=k;}
        cnt+=ct;
    }
    if(mx!=-1) flag[p]=flag[p^1]=true;
    return cnt;
}
void dfs2(int u,int fa)
{
    if(fa==-1) ft[u]=-1;
    else
    {
        if(flag[fa])
        {
            id[fa]=id[fa^1]=++N;val[N]=edges[fa].w;
            if(childs[edges[fa].u]<=1&&ft[edges[fa].u]!=-1) ft[u]=ft[edges[fa].u];
            else ft[u]=fa;
        }
        else ft[u]=-1;
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k!=(fa^1))
            dfs2(edges[k].v,k);
    }
}
int maxv[maxn<<2],minv[maxn<<2],neg[maxn<<2];
void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}
void PushDown(int rt)
{
    if(neg[rt])
    {
        neg[rt<<1]^=1;
        neg[rt<<1|1]^=1;
        int tmp=minv[rt<<1];
        minv[rt<<1]=-maxv[rt<<1];
        maxv[rt<<1]=-tmp;
        tmp=minv[rt<<1|1];
        minv[rt<<1|1]=-maxv[rt<<1|1];
        maxv[rt<<1|1]=-tmp;
        neg[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    neg[rt]=0;
    if(l==r)
    {
        minv[rt]=maxv[rt]=val[l];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return maxv[rt];
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1);
    return max(Query(L,R,l,m,rt<<1),Query(L,R,m+1,r,rt<<1|1));
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        neg[rt]=0;
        minv[rt]=maxv[rt]=v;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
void Negate(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        neg[rt]^=1;
        int tmp=minv[rt];
        minv[rt]=-maxv[rt];
        maxv[rt]=-tmp;
        return;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Negate(L,R,l,m,rt<<1);
    if(m<R) Negate(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
int findmax(int x,int y)
{
    if(x==y) return 0;
    int maxres=-inf,L,R;
    while(x!=y)
    {
        if(d[x]<d[y]) swap(x,y);
        if(ft[x]!=-1)
        {
            L=id[ft[x]];R=id[pa[x]];
            if(ft[x]==ft[y])
            {
                L=id[pa[y]]+1;
                x=y;
            }
            else x=edges[ft[x]].u;
            maxres=max(maxres,Query(L,R,1,N,1));
        }
        else
        {
            maxres=max(maxres,edges[pa[x]].w);
            x=edges[pa[x]].u;
        }
    }
    return maxres;
}
void negseg(int x,int y)
{
    if(x==y) return ;
    int L,R;
    while(x!=y)
    {
        if(d[x]<d[y]) swap(x,y);
        if(ft[x]!=-1)
        {
            L=id[ft[x]];R=id[pa[x]];
            if(ft[x]==ft[y])
            {
                L=id[pa[y]]+1;
                x=y;
            }
            else x=edges[ft[x]].u;
            Negate(L,R,1,N,1);
        }
        else
        {
            edges[pa[x]].w*=-1;
            x=edges[pa[x]].u;
        }
    }
}
void changes(int x,int v)
{
    if(flag[x*2]) Update(id[x*2],1,N,1,v);
    else edges[x*2].w=edges[(x*2)^1].w=v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    char str[10];
    while(t--)
    {
        Init();
        scanf("%d",&n);
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        dfs(1,-1);dfs2(1,-1);
        if(N) build(1,N,1);
        while(true)
        {
            scanf("%s",str);
            if(str[0]=='D') break;
            scanf("%d%d",&u,&v);
            if(str[0]=='Q')
            {
                w=findmax(u,v);
                printf("%d\n",w);
            }
            else if(str[0]=='N')
                negseg(u,v);
            else changes(u-1,v);
        }
    }
    return 0;
}

