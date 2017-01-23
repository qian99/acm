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
typedef long long ll;
const int maxn=1000;
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    vector<Edge>edges;
    vector<int>G[maxn];
    int m,n,s,t;
    int cur[maxn],d[maxn];
    bool vis[maxn];
    void ClearAll(int n)
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
        memset(vis,0,sizeof(vis));
        queue<int>q;
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
        for(int &i=cur[x];i<G[x].size();++i)
        {
            Edge e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
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
int coll[20][30];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        int N=n+m+1;
        int k,temp;
        memset(coll,0,sizeof(coll));
        for(int i=0;i<n;++i)
        {
            scanf("%d",&k);
            for(int j=0;j<k;++j)
            {
                scanf("%d",&temp);
                coll[i][temp]++;
            }
        }
        dinic.ClearAll(N);
        for(int i=1;i<=m;++i)
        {
            dinic.AddEdges(i,N,1);
            if(coll[0][i])
            dinic.AddEdges(0,i,coll[0][i]);
        }
        for(int i=1;i<n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                if(coll[i][j]>1) dinic.AddEdges(i+m,j,coll[i][j]-1);
                else if(coll[i][j]==0) dinic.AddEdges(j,i+m,1);
            }
        }
        int ans=dinic.Maxflow(0,N);
        printf("Case #%d: %d\n",tcase,ans);
    }
    return 0;
}
