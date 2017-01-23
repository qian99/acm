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
const int maxn=200+10;
struct Points
{
    int x,y;
};
struct Edge
{
    int from,to,cap,flow,cost;
};
struct MCMF
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    int inq[maxn],d[maxn],p[maxn],a[maxn];
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int cap,int cost)
    {
        edges.push_back((Edge){from,to,cap,0,cost});
        edges.push_back((Edge){to,from,0,0,-cost});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BellmanFord(int s,int t,int &flow,int &cost)
    {
        for(int i=0;i<=n;++i) d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0;inq[s]=1;p[s]=0;a[s]=inf;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            inq[u]=0;
            for(int i=0;i<G[u].size();++i)
            {
                Edge & e=edges[G[u][i]];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
                {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]) {q.push(e.to);inq[e.to]=1;}
                }
            }
        }
        if(d[t]==inf) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }
    int Mincost(int s,int t)
    {
        int flow=0;int cost=0;
        while(BellmanFord(s,t,flow,cost));
        return cost;
    }
}mcfc;
Points Home[maxn],Man[maxn];
char ss[maxn];
int length(Points a,Points b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int H=0,M=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",ss);
            for(int j=0;j<m;++j)
            {
                if(ss[j]=='m') Man[M++]=(Points){i,j};
                else if(ss[j]=='H') Home[H++]=(Points){i,j};
            }
        }
        int T=H+M+1;
        mcfc.Init(T);
        for(int i=0;i<M;++i)
        {
            mcfc.AddEdges(0,i+1,1,0);
            for(int j=0;j<H;++j)
              mcfc.AddEdges(i+1,M+j+1,inf,length(Man[i],Home[j]));
        }
        for(int i=0;i<H;++i)
           mcfc.AddEdges(M+i+1,T,1,0);
        int ans=mcfc.Mincost(0,T);
        printf("%d\n",ans);
    }
    return 0;
}
