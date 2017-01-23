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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=100+10;
struct Edge
{
    int from,to,cap,flow;
    bool operator < (const Edge a) const
    {
        return (from==a.from&&to<a.to)||from<a.from;
    }
};
struct Dinic
{
    vector<Edge>edges;
    vector<int>G[maxn];
    int n,m,s,t;
    int d[maxn],cur[maxn];
    bool vis[maxn];
    void clearAll(int n)
    {
        for(int i=0;i<=n;++i) G[i].clear();
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
        queue<int>q;
        memset(vis,0,sizeof(vis));
        q.push(s);
        d[s]=0;vis[s]=true;
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
        for(int& i=cur[x];i<G[x].size();++i)
        {
            Edge e=edges[G[x][i]];
            if(d[e.to]==d[x]+1&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
            {
                flow+=f;
                edges[G[x][i]].flow+=f;
                edges[G[x][i]^1].flow-=f;
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
    void clearFlow()
    {
        for(int i=0;i<edges.size();++i)
           edges[i].flow=0;
    }
    void Reduce()
    {
        for(int i=0;i<edges.size();++i)
           edges[i].cap-=edges[i].flow;
    }
    vector<int> Mincut()
    {
        vector<int>ans;
        for(int i=0;i<edges.size();++i)
        {
            Edge e=edges[i];
            if(vis[e.from]&&!vis[e.to]&&e.cap>0) ans.push_back(i);
        }
        return ans;
    }
}dinic;
Edge ans[10010];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int N,E,C;
    int tcase=0;
    while(~scanf("%d%d%d",&N,&E,&C))
    {
        if(N==0&&E==0&&C==0) break;
        tcase++;
        dinic.clearAll(N);
        int from,to,cap;
        for(int i=0;i<E;++i)
        {
            scanf("%d%d%d",&from,&to,&cap);
            dinic.AddEdges(from,to,cap);
        }
        printf("Case %d: ",tcase);
        int maxflow=dinic.Maxflow(1,N);
        if(maxflow>=C)
           printf("possible\n");
        else
        {
            int ss=0;
            vector<int>cut=dinic.Mincut();
            dinic.Reduce();
            for(int i=0;i<cut.size();++i)
            {
                Edge &e=dinic.edges[cut[i]];
                dinic.clearFlow();
                e.cap=C;
                int res=dinic.Maxflow(1,N);
                if(res+maxflow>=C) ans[ss++]=e;
                e.cap=0;
            }
            if(ss==0) printf("not possible\n");
            else
            {
                sort(ans,ans+ss);
                printf("possible option:(%d,%d)",ans[0].from,ans[0].to);
                for(int i=1;i<ss;++i)
                  printf(",(%d,%d)",ans[i].from,ans[i].to);
                printf("\n");
            }
        }
    }
    return 0;
}
