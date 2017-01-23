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
    int v,w;
    int next;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode &a) const
    {
        return d>a.d;
    }
};
Edge edges[maxn*6];
int head[maxn<<2],nEdge,n,m,c;
int d[maxn<<2];
bool vis[maxn<<2];
vector<int>layer[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void djkstra(int N)
{
    priority_queue<HeapNode>q;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i) d[i]=inf;
    d[1]=0;
    HeapNode hp;
    hp.u=1;hp.d=0;
    q.push(hp);
    while(!q.empty())
    {
        hp=q.top();q.pop();
        int u=hp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                hp.d=d[v];hp.u=v;
                q.push(hp);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int u,v,w,tmp;
        scanf("%d%d%d",&n,&m,&c);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<=n;++i) layer[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&tmp);
            layer[tmp].push_back(i);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        int sz;
        for(int i=1;i<n;++i)
        {
            sz=layer[i].size();
            for(int j=0;j<sz;++j)
            {
                AddEdge(layer[i][j],i+n,c);
                AddEdge(i+n+n,layer[i][j],0);
            }
            sz=layer[i+1].size();
            for(int j=0;j<sz;++j)
            {
                AddEdge(i+n,layer[i+1][j],0);
                AddEdge(layer[i+1][j],i+n+n,c);
            }
        }
        djkstra(n*3);
        printf("Case #%d: ",tcase);
        if(d[n]==inf||n==0)
          printf("-1\n");
        else printf("%d\n",d[n]);
    }
    return 0;
}
