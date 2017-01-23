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
    int v;
    int next;
};
Edge edges[maxn<<1];
bool flag[maxn<<1];
int head[maxn],color[maxn],id[maxn],nEdge;
int pt[maxn],pa[maxn],pax[maxn],child[maxn],belongs[maxn],cnt;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    nEdge=-1;cnt=0;
    memset(child,0xff,sizeof(child));
    memset(head,0xff,sizeof(head));
    memset(belongs,0xff,sizeof(belongs));
    memset(flag,0,sizeof(flag));
    memset(color,0,sizeof(color));
}
void dfs(int u,int fa)
{
    pt[u]=1;
    int maxp=0,e=-1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k==(fa^1)) continue;
        int v=edges[k].v;
        if(child[u]==-1) child[u]=k;
        else child[u]=inf;
        pa[v]=u;
        dfs(v,k);
        if(pt[v]>maxp)
        {
            maxp=pt[v];
            e=k;
        }
        pt[u]+=pt[v];
    }
    if(e!=-1) flag[e]=flag[e^1]=true;
}
void dfs2(int u,int fa)
{
    if(fa!=-1&&child[u]!=inf&&child[u]!=-1&&flag[fa]&&flag[child[u]])
    {
        ++cnt;
        id[cnt]=u;
        belongs[u]=cnt;
        if(belongs[pa[u]]==-1)
           pax[u]=u;
        else pax[u]=pax[pa[u]];
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k==(fa^1)) continue;
        dfs2(edges[k].v,k);
    }
}
struct SegTree
{
    int sum[maxn<<2],pos[maxn<<2];
    void build(int l,int r,int rt)
    {
        sum[rt]=0;pos[rt]=inf;
        if(l==r) return;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    void PushUp(int rt)
    {
        pos[rt]=min(pos[rt<<1],pos[rt<<1|1]);
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }
    int Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R)
          return pos[rt];
        int m=(l+r)>>1;
        if(m>=R)
          return Query(L,R,l,m,rt<<1);
        else if(m<L)
          return Query(L,R,m+1,r,rt<<1|1);
        else
          return min(Query(L,R,l,m,rt<<1),Query(L,R,m+1,r,rt<<1|1));
    }
    void Update(int p,int l,int r,int rt)
    {
        if(l==r)
        {
            sum[rt]^=1;
            if(sum[rt]) pos[rt]=l;
            else pos[rt]=inf;
            return ;
        }
        int m=(l+r)>>1;
        if(m>=p)
          Update(p,l,m,rt<<1);
        else Update(p,m+1,r,rt<<1|1);
        PushUp(rt);
    }
}tree;
int solve(int x)
{
    if(color[1]) return 1;
    int res=-1,tmp,L,R;
    while(x!=1)
    {
        if(belongs[x]==-1)
        {
            if(color[x])
              res=x;
            x=pa[x];
        }
        else
        {
            R=belongs[x];L=belongs[pax[x]];
            tmp=tree.Query(L,R,1,cnt,1);
            if(tmp!=inf) res=id[tmp];
            x=pa[pax[x]];
        }
    }
    return res;
}
void chc(int x)
{
    if(belongs[x]==-1) color[x]^=1;
    else tree.Update(belongs[x],1,cnt,1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        Init();
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        dfs(1,-1);
        dfs2(1,-1);
        if(cnt>0)
          tree.build(1,cnt,1);
        int a,b;
        while(q--)
        {
            scanf("%d%d",&a,&b);
            if(a==0) chc(b);
            else
            {
                int ans=solve(b);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
