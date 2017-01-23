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
//#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+100;
struct Edge
{
    ll from,to,cap,flow,cost;
};
struct MCFC
{
    vector<Edge>edges;
    vector<int>G[maxn];
    int m,n,s,t;
    ll d[maxn],inq[maxn],p[maxn],a[maxn];
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(ll from,ll to,ll cap,ll cost)
    {
        edges.push_back((Edge){from,to,cap,0,cost});
        edges.push_back((Edge){to,from,0,0,-cost});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool BellmanFord(ll s,ll t,ll & flow,ll & cost)
    {
        memset(inq,0,sizeof(inq));
        for(int i=0;i<=n;++i) d[i]=Inf;
        d[s]=0;p[s]=0;inq[s]=1;a[s]=Inf;
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
                    if(!inq[e.to]) {q.push(e.to);inq[e.to]=1;}
                }
            }
        }
        if(d[t]>0) return false;
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
    ll Mincost(int s,int t)
    {
        ll flow=0,cost=0;
        while(BellmanFord(s,t,flow,cost));
        return cost;
    }
}mcfc;
struct MonInfo
{
    int mi,ni,pi,si,E;
};
MonInfo mon[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int M,I;
        scanf("%d%d",&M,&I);
        int N=2*M+1;
        mcfc.Init(N);
        for(int i=1;i<=M;++i)
          scanf("%d%d%d%d%d",&mon[i].mi,&mon[i].ni,&mon[i].pi,&mon[i].si,&mon[i].E);
        for(int i=1;i<=M;++i)
        {
            mcfc.AddEdges(0,i,mon[i].ni,mon[i].mi);
            int z=min(M,mon[i].E+i);
            for(int j=i;j<=z;++j)
            {
                mcfc.AddEdges(i,M+j,Inf,(j-i)*I);
            }
        }
        for(int i=1;i<=M;++i)
           mcfc.AddEdges(i+M,N,mon[i].si,-mon[i].pi);
        ll ans=mcfc.Mincost(0,N);
        printf("Case %d: %lld\n",tcase,-ans);
    }
    return 0;
}
