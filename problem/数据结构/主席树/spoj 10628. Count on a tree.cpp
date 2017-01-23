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
struct Node
{
    int L,R;
    int sum;
}node[maxn*20*2];
struct Edge
{
    int v,next;
}edges[maxn<<1];
struct Data
{
    int w,pos;
    bool operator < (const Data &a)const
    {
        return w<a.w;
    }
}num[maxn];
struct Q
{
    int v,pos,k;
};
vector<Q>querys[maxn];
int node_cnt,n,q,nEdge;
int ans[maxn],d[maxn],head[maxn];
int root[maxn],rank[maxn],f[maxn];
int parents[maxn];
bool vis[maxn];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    for(int i=1;i<=n;++i) querys[i].clear();
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    f[1]=0;d[1]=1;
    node_cnt=0;nEdge=-1;
}
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
int build(int l,int r)
{
    int x=node_cnt++;
    node[x].sum=0;
    if(l==r) return x;
    int m=(l+r)>>1;
    node[x].L=build(l,m);
    node[x].R=build(m+1,r);
    return x;
}
int Update(int p,int l,int r,int rt)
{
    int x=node_cnt++;
    node[x]=node[rt];
    node[x].sum++;
    if(l==r) return x;
    int m=(l+r)>>1;
    if(p<=m)
      node[x].L=Update(p,l,m,node[x].L);
    else
      node[x].R=Update(p,m+1,r,node[x].R);
    return x;
}
int Query(int r1,int r2,int r3,int l,int r,int k,int s)
{
    if(l==r) return l;
    int m=(l+r)>>1;
    int tmp=node[node[r1].L].sum+node[node[r2].L].sum-node[node[r3].L].sum*2-(s>=l&&s<=m);
    if(tmp>=k)
      return Query(node[r1].L,node[r2].L,node[r3].L,l,m,k,s);
    else
      return Query(node[r1].R,node[r2].R,node[r3].R,m+1,r,k-tmp,s);
}
void tarjan(int u,int fa)
{
    parents[u]=u;
    vis[u]=true;
    root[u]=Update(rank[u],1,n,root[f[u]]);
    int sz=querys[u].size();
    Q tmp;
    for(int i=0;i<sz;++i)
    {
        tmp=querys[u][i];
        if(vis[tmp.v])
        {
            int anc=Find(tmp.v);
            ans[tmp.pos]=Query(root[u],root[tmp.v],root[f[anc]],1,n,tmp.k,rank[anc]);
        }
    }
    for(int h=head[u];h!=-1;h=edges[h].next)
    {
        int v=edges[h].v;
        if(v==fa) continue;
        d[v]=d[u]+1;f[v]=u;
        tarjan(v,u);
        parents[v]=u;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&q))
    {
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i].w);
            num[i].pos=i;
        }
        sort(num+1,num+n+1);
        for(int i=1;i<=n;++i)
          rank[num[i].pos]=i;
        int u,v,k;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        root[0]=build(1,n);
        Q tmp;
        for(int i=0;i<q;++i)
        {
            scanf("%d%d%d",&u,&v,&k);
            tmp.v=v;tmp.k=k;tmp.pos=i;
            querys[u].push_back(tmp);
            tmp.v=u;
            querys[v].push_back(tmp);
        }
        tarjan(1,-1);
        for(int i=0;i<q;++i)
          printf("%d\n",num[ans[i]].w);
    }
    return 0;
}
