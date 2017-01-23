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
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],d[maxn],color[maxn],nEdge;
int pa[maxn],fp[maxn],vson[maxn],id[maxn],cc[maxn],N;
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
    memset(id,0xff,sizeof(id));
    nEdge=-1;N=0;d[1]=0;
}
int dfs(int u,int fa)
{
    int childs=1,maxw=0,wv=-1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;
        pa[v]=u;
        int tmp=dfs(v,u);
        childs+=tmp;
        if(tmp>maxw) {maxw=tmp;wv=v;}
    }
    vson[u]=wv;
    return childs;
}
void dfs2(int u,int fa)
{
    if(vson[u]!=-1)
    {
        id[u]=++N;
        if(fa==-1||vson[fa]!=u) fp[u]=u;
        else fp[u]=fp[fa];
        dfs2(vson[u],u);
    }
    else if(fa==-1||vson[fa]==u)
        id[u]=++N,fp[u]=(fa==-1)?u:fp[fa];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||v==vson[u]) continue;
        fp[v]=v;
        dfs2(v,u);
    }
    if(id[u]!=-1) cc[id[u]]=color[u];
}
struct SegTree
{
    int sum[maxn<<2][11],cntc[11];
    void PushUp(int rt)
    {
        for(int i=1;i<=10;++i)
            sum[rt][i]=sum[rt<<1][i]+sum[rt<<1|1][i];
    }
    void build(int l,int r,int rt)
    {
        memset(sum[rt],0,sizeof(sum[rt]));
        sum[rt][cc[l]]=1;
        if(l==r) return ;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(rt);
    }
    void Update(int p,int l,int r,int rt,int c)
    {
        if(l==r)
        {
            memset(sum[rt],0,sizeof(sum[rt]));
            sum[rt][c]=1;
            return ;
        }
        int m=(l+r)>>1;
        if(m>=p) Update(p,l,m,rt<<1,c);
        else Update(p,m+1,r,rt<<1|1,c);
        PushUp(rt);
    }
    void Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R)
        {
            for(int i=1;i<=10;++i)
                cntc[i]+=sum[rt][i];
            return ;
        }
        int m=(l+r)>>1;
        if(m>=L) Query(L,R,l,m,rt<<1);
        if(m<R) Query(L,R,m+1,r,rt<<1|1);
    }
}tree;
int getMax(int x,int y)
{
    memset(tree.cntc,0,sizeof(tree.cntc));
    while(fp[x]!=fp[y])
    {
        if(d[fp[x]]<d[fp[y]]) swap(x,y);
        if(id[x]==-1) tree.cntc[color[x]]++;
        else tree.Query(id[fp[x]],id[x],1,N,1);
        x=pa[fp[x]];
    }
    if(d[x]<d[y]) swap(x,y);
    if(id[x]==-1) tree.cntc[color[x]]++;
    else tree.Query(id[y],id[x],1,N,1);
    int maxc=0;
    for(int i=1;i<=10;++i)
        if(tree.cntc[i]>maxc) maxc=tree.cntc[i];
    return maxc;
}
void changes(int x,int c)
{
    if(id[x]==-1) color[x]=c;
    else tree.Update(id[x],1,N,1,c);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init();
        for(int i=1;i<=n;++i)
            scanf("%d",&color[i]);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        dfs2(1,-1);
        tree.build(1,N,1);
        int type;
        while(m--)
        {
            scanf("%d%d%d",&type,&u,&v);
            if(type)
            {
                printf("%d\n",getMax(u,v));
            }
            else changes(u,v);
        }
    }
    return 0;
}
