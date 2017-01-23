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
const int maxn=200+10;
struct Edge
{
    int from,to,cap,flow,next;
};
struct Dinic
{
    Edge edges[maxn<<1];
    int head[maxn],d[maxn],cur[maxn];
    bool vis[maxn];
    int s,t,n,nEdge;
    void clear(int n)
    {
        this->n=n;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
    }
    void AddEdge(int from,int to,int cap)
    {
        nEdge++;edges[nEdge].from=from;edges[nEdge].to=to;
        edges[nEdge].cap=cap;edges[nEdge].flow=0;
        edges[nEdge].next=head[from];head[from]=nEdge;
        nEdge++;edges[nEdge].from=to;edges[nEdge].to=from;
        edges[nEdge].cap=edges[nEdge].flow=0;
        edges[nEdge].next=head[to];head[to]=nEdge;
    }
    bool bfs()
    {
        memset(vis,0,sizeof(vis));
        d[s]=0;vis[s]=true;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                Edge e=edges[k];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    d[e.to]=d[u]+1;
                    vis[e.to]=true;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int u,int a)
    {
        if(u==t||a==0) return a;
        int flow=0,f;
        for(int &k=cur[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[e.to]==d[u]+1)
            {
                f=dfs(e.to,min(a,e.cap-e.flow));
                if(f<=0) continue;
                edges[k].flow+=f;
                edges[k^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s,int t)
    {
        this->s=s;this->t=t;
        int res=0;
        while(bfs())
        {
            for(int i=0;i<=n;++i) cur[i]=head[i];
            res+=dfs(s,inf);
        }
        return res;
    }
}dinic;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    while(~scanf("%d%d",&m,&n))
    {
        int from,to,cap;
        dinic.clear(n);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&from,&to,&cap);
            dinic.AddEdge(from,to,cap);
        }
        int ans=dinic.MaxFlow(1,n);
        printf("%d\n",ans);
    }
    return 0;
}
