#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=50000+10;
const int maxm=3000000+10;
struct Edge
{
    int v,w,next;
};
struct HeapNode
{
    int d,u;
    bool operator <(const HeapNode & a) const
    {
        return a.d<d;
    }
};
Edge edges[maxm<<1];
int head[maxn];
int n,s,t,M,nEdge;
bool vis[maxn];
double d[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dijkstra()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i) d[i]=1e10;
    d[s]=0;
    priority_queue<HeapNode>q;
    HeapNode hp;
    hp.d=0;hp.u=s;
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
            if(d[v]>d[u]+(M-d[u])*edges[k].w/100)
            {
                d[v]=d[u]+(M-d[u])*edges[k].w/100;
                hp.d=d[v];hp.u=v;
                q.push(hp);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int k,v,w;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d%d",&v,&w);
                AddEdge(i,v,w);
                //AddEdge(v,i,w);
            }
        }
        scanf("%d%d%d",&s,&t,&M);
        dijkstra();
        double ans=d[t];
        if(ans>=1e10) printf("IMPOSSIBLE!\n");
        else
        printf("%.2lf\n",ans);
    }
    return 0;
}
