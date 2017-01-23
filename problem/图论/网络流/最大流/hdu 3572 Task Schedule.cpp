#include <iostream>
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
const int maxn=1000+10;
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    int m,n,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int d[maxn],cur[maxn];
    void clear(int n)
    {
        for(int i=0;i<n;++i) G[i].clear();
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
        queue<int>q;
        d[s]=0;vis[s]=true;
        q.push(s);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    d[e.to]=d[x]+1;
                    vis[e.to]=true;
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
            Edge & e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
            {
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
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
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,inf);
        }
        return flow;
    }
}dinic;
bool days[maxn/2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        dinic.clear(maxn);
        memset(days,0,sizeof(days));
        scanf("%d%d",&n,&m);
        int P,S,E,T=maxn-1,sum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&P,&S,&E);
            dinic.AddEdges(0,1,P);
            sum+=P;
            for(int j=S;j<=E;++j)
            {
                dinic.AddEdges(1,n+j,1);
                days[j]=true;
            }
        }
        for(int i=1;i<maxn/2;++i)
            if(days[i]) dinic.AddEdges(n+i,T,m);
        int res=dinic.Maxflow(0,T);
        printf("Case %d: ",tcase);
        if(res==sum) printf("Yes\n\n");
        else printf("No\n\n");
    }
    return 0;
}
