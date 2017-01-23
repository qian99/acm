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
const int maxn=200+10;
const int maxm=400000+10;
struct Edge
{
    int to,cap,flow;
    int next;
};
struct Dinic
{
    int n,s,t;
    Edge edges[maxm<<1];
    int head[maxn],nEdge;
    int d[maxn],cur[maxn];
    bool vis[maxn];
    void AddEdges(int from,int to,int cap)
    {
        nEdge++;edges[nEdge].to=to;
        edges[nEdge].cap=cap;edges[nEdge].flow=0;
        edges[nEdge].next=head[from];head[from]=nEdge;
        nEdge++;edges[nEdge].to=from;
        edges[nEdge].cap=0;edges[nEdge].flow=0;
        edges[nEdge].next=head[to];head[to]=nEdge;
    }
    void Init(int n)
    {
        this->n=n;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
    }
    bool BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int>q;
        d[s]=0;vis[s]=true;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                int v=edges[k].to;
                if(!vis[v]&&edges[k].cap>edges[k].flow)
                {
                    d[v]=d[u]+1;
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x,int a)
    {
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int & k=cur[x];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(e.cap-e.flow,a)))>0)
            {
                edges[k].flow+=f;
                edges[k^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s,int t)
    {
        this->s=s;this->t=t;
        int flow=0;
        while(BFS())
        {
            for(int i=0;i<=n;++i)
              cur[i]=head[i];
            flow+=DFS(s,inf);
        }
        return flow;
    }
}dinic;
int bnum[maxm],fnum[maxm];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        dinic.Init(n+1);
        int u,v,l,c,sum=0;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&l,&c);
            dinic.AddEdges(u,v,c-l);
            bnum[i]=dinic.nEdge-1;
            fnum[i]=l;
            dinic.AddEdges(0,v,l);
            dinic.AddEdges(u,n+1,l);
            sum+=l;
        }
        dinic.AddEdges(n+1,0,inf);
        int maxflow=dinic.Maxflow(0,n+1);
        if(maxflow!=sum)
          printf("NO\n");
        else
        {
            printf("YES\n");
            for(int i=0;i<m;++i)
              printf("%d\n",dinic.edges[bnum[i]].flow+fnum[i]);
        }
    }
    return 0;
}
