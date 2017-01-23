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
    int u,v,w;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],cntp[maxn],cnts[maxn],d[maxn],nEdge,n;
int lchain[maxn],lp[maxn],parents[maxn],num[maxn<<1],cntb;
int aa[maxn];
bool heav[maxn<<1];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].u=u;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    int mx=-inf,e;
    cntp[u]=1;
    cnts[u]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        parents[v]=k;
        d[v]=d[u]+1;
        dfs(v,u);
        cnts[u]++;
        cntp[u]+=cntp[v];
        if(cntp[v]>mx)
        {
            mx=cntp[v];
            e=k;
        }
    }
    if(mx>0)
      heav[e]=heav[e^1]=true;
}
void dfs2(int u,int fa)
{
    lchain[u]=lp[u]=-1;
    if(fa>0)
    {
        if(heav[fa])
        {
            int tu=edges[fa].u;
            if(cnts[tu]<=1&&lp[tu]>0)
              lp[u]=lp[tu];
            else lp[u]=fa;
            lchain[u]=fa;
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(k==(fa^1)) continue;
        if(heav[k])
        {
            num[k]=num[k^1]=++cntb;
            aa[cntb]=edges[k].w;
        }
        dfs2(v,k);
    }
}
struct SegTree
{
    int maxv[maxn<<2];
    void PushUp(int rt)
    {
        maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    }
    void build(int l,int r,int rt)
    {
        if(l==r)
        {
            maxv[rt]=aa[l];
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
          return maxv[rt];
        int m=(l+r)>>1;
        int res=-1;
        if(m>=L)
         res=max(res,Query(L,R,l,m,rt<<1));
        if(m<R)
         res=max(res,Query(L,R,m+1,r,rt<<1|1));
        return res;
    }
    void Update(int p,int l,int r,int rt,int v)
    {
        if(l==r)
        {
            maxv[rt]=v;
            return ;
        }
        int m=(l+r)>>1;
        if(p<=m)
          Update(p,l,m,rt<<1,v);
        else Update(p,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
}tree;
int fmax(int x,int y)
{
    int res=0;
    while(x!=y)
    {
        if(d[y]>d[x])
          swap(x,y);
        if(lchain[x]<0)
        {
            res=max(res,edges[parents[x]].w);
            x=edges[parents[x]].u;
        }
        else
        {
            int L=lp[x],R=lchain[x];
            x=edges[L].u;
            if(L==lp[y])
            {
                L=lchain[y];
                L=num[L]+1;
                x=y;
            }
            else L=num[L];
            R=num[R];
            res=max(res,tree.Query(L,R,1,cntb,1));
        }
    }
    return res;
}
void chm(int x,int v)
{
    if(heav[x<<1])
      tree.Update(num[x*2],1,cntb,1,v);
    else edges[x*2].w=edges[x*2+1].w=v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[10];
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        nEdge=1;
        memset(head,0xff,sizeof(head));
        memset(heav,0,sizeof(heav));
        cntb=0;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        d[1]=0;lchain[1]=-1;lp[1]=-1;
        dfs(1,-1);
        dfs2(1,-1);
        tree.build(1,cntb,1);
        while(~scanf("%s",str))
        {
            if(str[0]=='D') break;
            scanf("%d%d",&u,&v);
            if(str[0]=='Q')
            {
                int ans=fmax(u,v);
                printf("%d\n",ans);
            }
            else chm(u,v);
        }
    }
    return 0;
}
