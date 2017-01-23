#pragma comment(linker,"/STACK:100000000,100000000")
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
const int maxn=50000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxn<<1];
bool heav[maxn<<1],flag[maxn];
int head[maxn],nEdge,n,m,q,N;
int val[maxn],childs[maxn],d[maxn],w[maxn];
int fp[maxn],pa[maxn],id[maxn],pt[maxn];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    memset(d,0,sizeof(d));
    memset(heav,0,sizeof(heav));
    memset(head,0xff,sizeof(head));
    memset(childs,0xff,sizeof(childs));
    memset(flag,0,sizeof(flag));
    memset(id,0xff,sizeof(id));
    nEdge=-1;N=0;d[1]=1;
}
void dfs(int u,int fa)
{
    int tmp=-1,ee;
    pt[u]=1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(childs[u]==-1) childs[u]=k;
        else childs[u]=inf;
        pa[v]=u;d[v]=d[u]+1;
        dfs(v,u);
        pt[u]+=pt[v];
        if(pt[v]>tmp);
        {
            tmp=pt[v];
            ee=k;
        }
    }
    if(tmp!=-1) heav[ee]=heav[ee^1]=true;
}
void dfs2(int u,int fa)
{
    if(fa!=-1&&childs[u]!=inf&&childs[u]!=-1&&heav[childs[u]]&&heav[fa])
    {
        flag[u]=true;
        id[u]=++N;
        w[N]=val[u];
        if(id[pa[u]]==-1) fp[u]=u;
        else fp[u]=fp[pa[u]];
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k==(fa^1)) continue;
        dfs2(edges[k].v,k);
    }
}
struct SegTree
{
    int sumv[maxn<<2],addv[maxn<<2];
    void PushUp(int rt)
    {
        sumv[rt]=sumv[rt<<1]+sumv[rt<<1|1];
    }
    void PushDown(int l,int r,int rt)
    {
        if(addv[rt])
        {
            int m=(l+r)>>1;
            addv[rt<<1]+=addv[rt];
            addv[rt<<1|1]+=addv[rt];
            sumv[rt<<1]+=(m-l+1)*addv[rt];
            sumv[rt<<1|1]+=(r-m)*addv[rt];
            addv[rt]=0;
        }
    }
    void build(int l,int r,int rt)
    {
        addv[rt]=0;
        if(l==r)
        {
            sumv[rt]=w[l];
            return ;
        }
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(rt);
    }
    int Query(int p,int l,int r,int rt)
    {
        if(l==r) return sumv[rt];
        int m=(l+r)>>1;
        PushDown(l,r,rt);
        if(m>=p) return Query(p,l,m,rt<<1);
        return Query(p,m+1,r,rt<<1|1);
    }
    void Update(int L,int R,int l,int r,int rt,int v)
    {
        if(l>=L&&r<=R)
        {
            addv[rt]+=v;
            sumv[rt]+=(r-l+1)*v;
            return ;
        }
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        if(m>=L)
          Update(L,R,l,m,rt<<1,v);
        if(m<R)
          Update(L,R,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
}tree;
int qs(int x)
{
    if(flag[x]) return tree.Query(id[x],1,N,1);
    return val[x];
}
void solve(int x,int y,int v)
{
    if(x==y)
    {
        if(!flag[x]) val[x]+=v;
        else tree.Update(id[x],id[x],1,N,1,v);
        return ;
    }
    if(d[x]<d[y]) swap(x,y);
    while(true)
    {
        if(flag[x])
        {
            if(flag[y]&&fp[x]==fp[y])
            {
                tree.Update(id[y],id[x],1,N,1,v);
                break;
            }
            tree.Update(id[fp[x]],id[x],1,N,1,v);
            x=pa[fp[x]];
        }
        else
        {
            val[x]+=v;
            x=pa[x];
        }
        if(x==y)
        {
            if(flag[x]) tree.Update(id[x],id[x],1,N,1,v);
            else val[x]+=v;
            break;
        }
        if(d[x]<d[y]) swap(x,y);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        Init();
        for(int i=1;i<=n;++i)
          scanf("%d",&val[i]);
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        dfs(1,-1);
        dfs2(1,-1);
        if(N)
        tree.build(1,N,1);
        char str[5];
        int x,y;
        while(q--)
        {
            scanf("%s",str);
            if(str[0]=='I')
            {
                scanf("%d%d%d",&x,&y,&v);
                solve(x,y,v);
            }
            else if(str[0]=='D')
            {
                scanf("%d%d%d",&x,&y,&v);
                solve(x,y,-v);
            }
            else
            {
                scanf("%d",&x);
                printf("%d\n",qs(x));
            }
        }
    }
    return 0;
}
