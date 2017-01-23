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
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    vector<Edge>edges;
    vector<int>G[maxn];
    int m,n,s,t;
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
        for(int &i=cur[x];i<G[x].size();++i)
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
    void setCap(int s,int t,int cap)
    {
        for(int i=0;i<G[s].size();++i)
           edges[G[s][i]].cap=cap;
        for(int i=0;i<G[t].size();++i)
           edges[G[t][i]^1].cap=cap;
    }
}dinic;
int parents[maxn];
int bf[maxn*maxn][2];
bool flag[maxn][maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
    }
}
bool test(int s,int t,int m,int n)
{
    dinic.clearFlow();
    dinic.setCap(s,t,m);
    return m*n<=dinic.Maxflow(s,t);
}
int ff(int s,int t,int n)
{
    int l=0,r=n;
    int tmp=0;
    while(l<=r)
    {
        int m=(l+r)/2;
        if(test(s,t,m,n))
        {
            l=m+1;
            tmp=m;
        }
        else
          r=m-1;
    }
    return tmp;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,f;
        scanf("%d%d%d",&n,&m,&f);
        int N=n*2+1;
        for(int i=0;i<=n;++i) parents[i]=i;
        dinic.clearAll(N);
        int a,b;
        for(int i=0;i<m;++i)
            scanf("%d%d",&bf[i][0],&bf[i][1]);
        for(int i=0;i<f;++i)
        {
            scanf("%d%d",&a,&b);
            Uion(a,b);
        }
        memset(flag,0,sizeof(flag));
        for(int i=0;i<m;++i)
        {
            a=bf[i][0];
            b=bf[i][1];
            for(int j=1;j<=n;++j)
            {
                if(Find(a)==Find(j)&&!flag[j][b])
                {
                    flag[j][b]=true;
                    dinic.AddEdges(j,b+n,1);
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            dinic.AddEdges(0,i,0);
            dinic.AddEdges(i+n,N,0);
        }
        //int ans=dinic.Maxflow(0,N);
        int ans=ff(0,N,n);
        printf("%d\n",ans);
    }
    return 0;
}
