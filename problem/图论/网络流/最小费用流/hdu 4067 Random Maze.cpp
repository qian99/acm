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
    bool spfa(int s,int t,int &flow,int &cost)
    {
        for(int i=0;i<=n;++i) d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0;inq[s]=true;p[s]=0;a[s]=inf;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            inq[u]=false;
            for(int i=0;i<G[u].size();++i)
            {
                Edge &e=edges[G[u][i]];
                if(e.cap>e.flow&&e.cost+d[u]<d[e.to])
                {
                    d[e.to]=e.cost+d[u];
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]) {q.push(e.to);inq[e.to]=true;}
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
    void Mincost(int s,int t,int &flow,int &cost)
    {
        flow=0;cost=0;
        while(spfa(s,t,flow,cost));
    }
}mcfc;
int ind[maxn],outd[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,tcase=0;
    int n,m,s,t;
    scanf("%d",&T);
    while(T--)
    {
        tcase++;
        scanf("%d%d%d%d",&n,&m,&s,&t);
        mcfc.Init(n+1);
        int u,v,a,b;
        int sum=0,cnt=0;
        memset(ind,0,sizeof(ind));
        memset(outd,0,sizeof(outd));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&a,&b);
            if(a>b)
            {
                mcfc.AddEdges(u,v,1,a-b);
                sum+=b;
            }
            else
            {
                mcfc.AddEdges(v,u,1,b-a);
                sum+=a;
                outd[u]++;ind[v]++;
            }
        }
        ind[s]++;outd[t]++;
        for(int i=1;i<=n;++i)
        {
            if(ind[i]>outd[i])
              mcfc.AddEdges(0,i,ind[i]-outd[i],0);
            else if(ind[i]<outd[i])
            {
                mcfc.AddEdges(i,n+1,outd[i]-ind[i],0);
                cnt+=(outd[i]-ind[i]);
            }
        }
        int flow,cost;
        mcfc.Mincost(0,n+1,flow,cost);
        printf("Case %d: ",tcase);
        if(flow==cnt)
           printf("%d\n",cost+sum);
        else printf("impossible\n");
    }
    return 0;
}
