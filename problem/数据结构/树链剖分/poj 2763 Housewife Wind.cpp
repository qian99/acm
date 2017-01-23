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
const int maxn=100000+10;
struct Edge
{
    int u,v,w,next;
    Edge (){};
    Edge (int uu,int vv,int ww,int nx) {u=uu;v=vv;w=ww;next=nx;}
}edges[maxn<<1];
int head[maxn],d[maxn],nEdge,N;
int childs[maxn],pa[maxn],ft[maxn],id[maxn<<1],val[maxn];
bool flag[maxn<<1];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(u,v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(v,u,w,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(d,0,sizeof(d));
    memset(flag,0,sizeof(flag));
    memset(ft,0xff,sizeof(ft));
    nEdge=-1;N=0;
}
//划分轻重边
int dfs(int u,int fa)
{
    childs[u]=0;
    int cc=1;
    int maxb=-1,pos;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        pa[v]=k;childs[u]++;
        d[v]=d[u]+1;
        int cv=dfs(v,u);
        cc+=cv;
        if(cv>maxb) {maxb=cv;pos=k;}
    }
    if(maxb!=-1) flag[pos]=flag[pos^1]=true;
    return cc;
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
        if(k==(fa^1)) continue;
        dfs2(edges[k].v,k);
    }
}
//线段树部分
int sum[maxn<<2];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=val[l];
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
        return sum[rt];
    }
    int m=(l+r)>>1;
    int res=0;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]=v;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int solve(int x,int y)
{
    if(x==y) return 0;
    int res=0,L,R;
    while(x!=y)
    {
        if(d[x]<d[y]) swap(x,y);
        if(ft[x]!=-1)
        {
            L=id[ft[x]];R=id[pa[x]];
            if(ft[y]==ft[x])
            {
                L=id[pa[y]]+1;
                x=y;
            }
            else x=edges[ft[x]].u;
            res+=Query(L,R,1,N,1);
        }
        else
        {
            res+=edges[pa[x]].w;
            x=edges[pa[x]].u;
        }
    }
    return res;
}
void change(int v,int w)
{
    if(flag[v*2]) Update(id[v*2],1,N,1,w);
    else edges[v*2].w=edges[(v*2)^1].w=w;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q,s;
    scanf("%d%d%d",&n,&q,&s);
    Init();
    int u,v,w;
    for(int i=1;i<n;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdges(u,v,w);
    }
    dfs(1,-1);dfs2(1,-1);
    if(N) build(1,N,1);
    int type,ans;
    while(q--)
    {
        scanf("%d",&type);
        if(type==0)
        {
            scanf("%d",&v);
            ans=solve(s,v);
            printf("%d\n",ans);
            s=v;
        }
        else
        {
            scanf("%d%d",&v,&w);
            change(v-1,w);
        }
    }
    return 0;
}
