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
const int maxn=100+10;
struct Edge
{
    int from,to,cap,flow,cost;
};
struct MCMF
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    int inq[maxn],d[maxn],a[maxn],p[maxn];
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i)
           G[i].clear();
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
    bool BellmanFord(int s,int t,int & flow,int & cost)
    {
        for(int i=0;i<=n;++i) d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0;inq[s]=1;a[s]=inf;p[s]=0;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            inq[u]=0;
            for(int i=0;i<G[u].size();++i)
            {
                Edge e=edges[G[u][i]];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
                {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]) { inq[e.to]=1;q.push(e.to);}
                }
            }
        }
        if(d[t]==inf) return false;
        flow+=a[t];
        cost+=a[t]*d[t];
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
        int flow=0,cost=0;
        while(BellmanFord(s,t,flow,cost))
        {
            if(flow==2) return cost;
        }
        return -1;
    }
}mcfc;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d",&m);
        int a,b,c;
        mcfc.Init(n);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            mcfc.AddEdges(a,b,1,c);
            mcfc.AddEdges(b,a,1,c);
        }
        int ans=mcfc.Mincost(1,n);
        if(ans!=-1)
           printf("%d\n",ans);
        else
           printf("Back to jail\n");
    }
    return 0;
}
