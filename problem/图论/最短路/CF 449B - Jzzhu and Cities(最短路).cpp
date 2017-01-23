#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int maxm=300000+10;
struct Edge
{
    int v,w,next;
    Edge(int v=0,int w=0,int next=0):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
int direct[maxn];
ll d[maxn];
bool inq[maxn],flag[maxn];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
struct HeapNode
{
    ll d;
    int u,type;
    HeapNode(ll d=0,int u=0,int type=0):d(d),u(u),type(type){}
    bool operator < (const HeapNode & a) const
    {
        if(a.d==d) return type<a.type;
        return a.d<d;
    }
};
bool vis[maxn];
int dijkstra(int n)
{
    int cnt=0;
    priority_queue<HeapNode>q;
    memset(vis,0,sizeof(vis));
    memset(flag,0,sizeof(flag));
    for(int i=1;i<=n;++i) d[i]=Inf;
    d[1]=0;
    HeapNode hp=HeapNode(0,1,0);
    for(int i=1;i<=n;++i)
        if(direct[i]!=-1) {cnt++;q.push(HeapNode(direct[i],i,-1));d[i]=direct[i];}
    q.push(hp);
    while(!q.empty())
    {
       hp=q.top();q.pop();
       int u=hp.u;
       if(vis[u]) continue;
       vis[u]=true;
       if(hp.type<0) cnt--;
       for(int k=head[u];k!=-1;k=edges[k].next)
       {
           int v=edges[k].v;
           if(d[v]>=d[u]+edges[k].w)
           {
               d[v]=d[u]+edges[k].w;
               q.push(HeapNode(d[v],v,0));
           }
       }
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    memset(head,0xff,sizeof(head));
    memset(direct,0xff,sizeof(direct));
    nEdge=-1;
    int u,v,w;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdges(u,v,w);
    }
    int ans=0;
    for(int i=0;i<k;++i)
    {
        scanf("%d%d",&u,&w);
        if(direct[u]==-1) direct[u]=w;
        else direct[u]=min(direct[u],w),ans++;
    }
    ans+=dijkstra(n);
    printf("%d\n",ans);
    return 0;
}