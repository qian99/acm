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
    int u,v,next;
    Edge(){};
    Edge(int uu,int vv,int nx) {u=uu;v=vv;next=nx;}
}edges[maxn<<1];
int d[maxn],pa[maxn],fp[maxn],vson[maxn],num[maxn];
int head[maxn],id[maxn],val[maxn],nEdge,N,n;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(u,v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(v,u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(d,0,sizeof(d));
    memset(vson,0xff,sizeof(vson));
    memset(id,0xff,sizeof(id));
    nEdge=-1;N=0;
}
int dfs(int u,int fa)
{
    int csum=1,cmax=0,me=-1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;pa[v]=u;
        int cc=dfs(v,u);
        csum+=cc;
        if(cc>cmax) {cmax=cc;me=v;}
    }
    vson[u]=me;
    return csum;
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
}
struct SegTree
{
    int sum[maxn<<2],maxs[maxn<<2];
    int mpre[maxn<<2],msuff[maxn<<2],setv[maxn<<2];
    void PushUp(int rt)
    {
        int ls=rt<<1,rs=rt<<1|1;
        sum[rt]=sum[ls]+sum[rs];
        maxs[rt]=max(maxs[ls],maxs[rs]);
        maxs[rt]=max(maxs[rt],msuff[ls]+mpre[rs]);
        mpre[rt]=max(mpre[ls],sum[ls]+mpre[rs]);
        msuff[rt]=max(msuff[rs],sum[rs]+msuff[ls]);
    }
    void PushDown(int l,int r,int rt)
    {
        if(setv[rt]!=-inf)
        {
            int ls=rt<<1,rs=rt<<1|1,m=(l+r)>>1;
            setv[ls]=setv[rs]=setv[rt];
            sum[ls]=(m-l+1)*setv[rt];
            sum[rs]=(r-m)*setv[rt];
            if(setv[rt]>0)
            {
                mpre[ls]=msuff[ls]=maxs[ls]=sum[ls];
                mpre[rs]=msuff[rs]=maxs[rs]=sum[rs];
            }
            else
            {
                mpre[ls]=msuff[ls]=maxs[ls]=setv[rt];
                mpre[rs]=msuff[rs]=maxs[rs]=setv[rt];
            }
            setv[rt]=-inf;
        }
    }
    void build(int l,int r,int rt)
    {
        setv[rt]=-inf;
        if(l==r)
        {
            sum[rt]=maxs[rt]=mpre[rt]=msuff[rt]=val[l];
            return ;
        }
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(rt);
    }
    int Query(int L,int R,int l,int r,int rt,int &qsum,int &mp,int &ms)
    {
        if(l>=L&&r<=R)
        {
            qsum=sum[rt];mp=mpre[rt];ms=msuff[rt];
            return maxs[rt];
        }
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        if(m>=R) return Query(L,R,l,m,rt<<1,qsum,mp,ms);
        else if(m<L) return Query(L,R,m+1,r,rt<<1|1,qsum,mp,ms);
        else
        {
            int qsum1,qsum2,mp1,mp2,ms1,ms2;
            int s1=Query(L,R,l,m,rt<<1,qsum1,mp1,ms1);
            int s2=Query(L,R,m+1,r,rt<<1|1,qsum2,mp2,ms2);
            s1=max(s1,s2);
            s1=max(s1,ms1+mp2);
            qsum=qsum1+qsum2;
            mp=max(mp1,qsum1+mp2);
            ms=max(ms2,qsum2+ms1);
            return s1;
        }
    }
    void Update(int L,int R,int l,int r,int rt,int v)
    {
        if(l>=L&&r<=R)
        {
            setv[rt]=v;
            sum[rt]=(r-l+1)*v;
            if(v>0)
                mpre[rt]=msuff[rt]=maxs[rt]=sum[rt];
            else
                mpre[rt]=msuff[rt]=maxs[rt]=v;
            return ;
        }
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        if(m>=L) Update(L,R,l,m,rt<<1,v);
        if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
}segtree;
int getMax(int x,int y)
{
    int xmax=0,ymax=0,xsuf=0,ysuf=0;
    int qsum,mp,ms,tmp;
    while(fp[x]!=fp[y])
    {
        if(d[fp[x]]<d[fp[y]])
        {
            swap(x,y);swap(xmax,ymax);
            swap(xsuf,ysuf);
        }
        if(id[x]==-1) {xmax=max(xmax,num[x]);xsuf=max(xsuf,num[x]);}
        else
        {
            tmp=segtree.Query(id[fp[x]],id[x],1,N,1,qsum,mp,ms);
            xmax=max(xmax,tmp);
            xmax=max(xmax,xsuf+ms);
            xsuf=max(mp,qsum+xsuf);
        }
        x=pa[fp[x]];
    }
    if(d[x]<d[y])
    {
        swap(x,y);swap(xmax,ymax);
        swap(xsuf,ysuf);
    }
    if(id[x]==-1) {xmax=max(xmax,num[x]);xsuf=max(xsuf,num[x]);}
    else
    {
        tmp=segtree.Query(id[y],id[x],1,N,1,qsum,mp,ms);
        xmax=max(xmax,tmp);
        xmax=max(xmax,xsuf+ms);
        xsuf=max(mp,qsum+xsuf);
    }
    xmax=max(xmax,ymax);
    xmax=max(xmax,xsuf+ysuf);
    return max(xmax,0);
}
void changes(int x,int y,int v)
{
    while(fp[x]!=fp[y])
    {
        if(d[fp[x]]<d[fp[y]]) swap(x,y);
        if(id[x]==-1) num[x]=v;
        else segtree.Update(id[fp[x]],id[x],1,N,1,v);
        x=pa[fp[x]];
    }
    if(d[x]<d[y]) swap(x,y);
    if(id[x]==-1) num[x]=v;
    else segtree.Update(id[y],id[x],1,N,1,v);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        Init();
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        dfs2(1,-1);
        for(int i=1;i<=n;++i)
            if(id[i]!=-1) val[id[i]]=num[i];
        if(N) segtree.build(1,N,1);
        int q,type,a,b,c;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&type);
            if(type==1)
            {
                scanf("%d%d",&a,&b);
                printf("%d\n",getMax(a,b));
            }
            else
            {
                scanf("%d%d%d",&a,&b,&c);
                changes(a,b,c);
            }
        }
    }
    return 0;
}

