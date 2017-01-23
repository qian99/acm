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
const int maxn=3000+10;
const int maxm=70000+10;
struct Edge
{
    int v,w,next;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode &a) const
    {
        return d>a.d;
    }
};
Edge edges[maxm<<1];
int head[maxn],pro[maxn],nEdge,n,m;
bool vis[maxn];
ll d[maxn],dt[maxn];
vector<int>lim[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    for(int i=0;i<=n;++i) lim[i].clear();
    memset(head,0xff,sizeof(head));
    memset(dt,0,sizeof(dt));
    memset(pro,0,sizeof(pro));
    memset(vis,0,sizeof(vis));
    nEdge=-1;
}
void dijkstra()
{
    for(int i=1;i<=n;++i) d[i]=Inf;
    d[1]=0;
    priority_queue<HeapNode>q;
    HeapNode hp;
    hp.d=0;hp.u=1;
    q.push(hp);
    int u,v,sz;
    while(!q.empty())
    {
        hp=q.top();q.pop();
        u=hp.u;
        if(vis[u]) continue;
        vis[u]=true;
        sz=lim[u].size();
        for(int i=0;i<sz;++i)
        {
            v=lim[u][i];
            pro[v]--;
            dt[v]=max(dt[v],d[u]);
            if(pro[v]==0&&d[v]!=Inf)
            {
                d[v]=max(dt[v],d[v]);
                hp.u=v;hp.d=d[v];
                q.push(hp);
            }
        }
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=max(d[u]+edges[k].w,dt[v]);
                hp.u=v;hp.d=d[v];
                if(pro[v]==0) q.push(hp);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init();
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            //AddEdge(v,u,w);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&u);
            pro[i]=u;
            while(u--)
            {
                scanf("%d",&v);
                lim[v].push_back(i);
            }
        }
        dijkstra();
        printf("%I64d\n",d[n]);
    }
    return 0;
}
