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
    int v,w;
    int next;
};
Edge edges[maxn<<1];
bool vis[maxn<<1];
int head[maxn],nEdge;
int pt[maxn],wp,maxp,sp,k;
int d[maxn],len[maxn],cnt,ans;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    vis[nEdge]=false;
    head[u]=nEdge;
}
void findroot(int u,int fa)
{
    pt[u]=1;
    int tmp=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||vis[k]) continue;
        findroot(v,u);
        tmp=max(pt[v],tmp);
        pt[u]+=pt[v];
    }
    tmp=max(tmp,sp-pt[u]);
    if(tmp<maxp)
    {
        maxp=tmp;
        wp=u;
    }
}
void fd(int u,int fa)
{
    pt[u]=1;
    d[cnt++]=len[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||vis[k]) continue;
        len[v]=len[u]+edges[k].w;
        fd(v,u);
        pt[u]+=pt[v];
    }
}
inline int cal(int x,int s)
{
    cnt=0;
    len[x]=s;
    fd(x,-1);
    sort(d,d+cnt);
    int ret=0,l=0,r=cnt-1;
    while(l<r)
    {
        if(d[l]+d[r]<=k)
        {
            ret+=(r-l);
            l++;
        }
        else r--;
    }
    return ret;
}
void work(int root)
{
    ans+=cal(root,0);
    for(int k=head[root];k!=-1;k=edges[k].next)
    {
        if(vis[k]) continue;
        vis[k]=vis[k^1]=true;
        int v=edges[k].v;
        ans-=cal(v,edges[k].w);
        sp=pt[v];
        maxp=inf;
        findroot(v,-1);
        work(wp);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d%d",&n,&k))
    {
        if(n==0&&k==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        ans=0;maxp=inf;sp=n;
        findroot(1,-1);
        work(wp);
        printf("%d\n",ans);
    }
    return 0;
}
