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
const int maxn=2000+10;
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    vector<Edge>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int d[maxn],cur[maxn];
    int n,m,s,t;
    void Init(int n)
    {
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int cap)
    {
        Edge e;e.from=from;e.to=to;e.cap=cap;e.flow=0;
        edges.push_back(e);
        e.from=to;e.to=from;e.cap=0;e.flow=0;
        edges.push_back(e);
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BFS()
    {
        queue<int>q;
        memset(vis,0,sizeof(vis));
        vis[s]=true;
        d[s]=0;
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
}dinic;
int states[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    while(~scanf("%d%d",&n,&m))
    {
        int temp=0,st;
        memset(states,0,sizeof(states));
        int total=1<<m;
        for(int i=0;i<n;++i)
        {
            st=0;
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&temp);
                st=(st<<1)+temp;
            }
            states[st]++;
        }
        int T=total+m+1;
        dinic.Init(T);
        for(int i=0;i<total;++i)
        {
            if(states[i])
            {
                dinic.AddEdges(0,i+1,states[i]);
                int j=m;
                int k=i;
                while(k!=0)
                {
                    int z=k&1;
                    if(z) dinic.AddEdges(i+1,total+j,inf);
                    k=k>>1;
                    j--;
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&temp);
            dinic.AddEdges(i+total,T,temp);
        }
        int res=dinic.Maxflow(0,T);
        if(res==n)
           printf("YES\n");
        else
           printf("NO\n");
    }
    return 0;
}
