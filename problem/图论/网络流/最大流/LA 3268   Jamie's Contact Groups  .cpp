#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    int d[maxn],cur[maxn];
    bool vis[maxn];
    void clearAll(int n)
    {
        for(int i=0;i<=n;++i)
           G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int cap)
    {
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BFS()
    {
       memset(vis,0,sizeof(vis));
       d[s]=0;vis[s]=true;
       queue<int>q;
       q.push(s);
       while(!q.empty())
       {
           int x=q.front();q.pop();
           for(int i=0;i<G[x].size();++i)
           {
               Edge e=edges[G[x][i]];
               if(!vis[e.to]&&e.cap>e.flow)
               {
                   vis[e.to]=true;
                   d[e.to]=d[x]+1;
                   q.push(e.to);
               }
           }
       }
       return vis[t];
    }
    int DFS(int x,int a)
    {
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int & i=cur[x];i<G[x].size();++i)
        {
            Edge e=edges[G[x][i]];
            if(d[e.to]==d[x]+1&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
            {
                edges[G[x][i]].flow+=f;
                edges[G[x][i]^1].flow-=f;
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
        int flow=0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,inf);
        }
        return flow;
    }
    void clearFlow()
    {
        for(int i=0;i<edges.size();++i)
           edges[i].flow=0;
    }
}dinic;
char name[50];
bool test(int S,int T,int n,int m,int mid)
{
    dinic.clearFlow();
    for(int i=n+1;i<=n+m;++i)
    {
        for(int j=0;j<dinic.G[i].size();++j)
        {
            Edge & e=dinic.edges[dinic.G[i][j]];
            if(e.cap>e.flow)
                e.cap=mid;
        }
    }
    return (dinic.MaxFlow(S,T)==n);
}
int f(int S,int T,int n,int m)
{
    int L=1,R=n;
    int mid;
    while(L<R)
    {
        mid=(L+R)>>1;
        if(test(S,T,n,m,mid))
            R=mid;
        else
            L=mid+1;
    }
    return L;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int S=0,T=n+m+1;
        int tmp;
        dinic.clearAll(T);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",name);
            while(true)
            {
                scanf("%d",&tmp);
                dinic.AddEdges(i,n+tmp+1,inf);
                if(getchar()=='\n') break;
            }
        }
        for(int i=1;i<=n;++i)
           dinic.AddEdges(S,i,1);
        for(int i=1;i<=m;++i)
           dinic.AddEdges(i+n,T,1);
        int ans=f(S,T,n,m);
        printf("%d\n",ans);
    }
    return 0;
}
