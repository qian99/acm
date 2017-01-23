#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
const int maxm=100000+10;
struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
};
struct Node
{
    Point pos;
    int s,t,worker[6];
    void read(int n)
    {
        scanf("%lf%lf",&pos.x,&pos.y);
        scanf("%d%d",&s,&t);
        for(int i=0;i<n;++i)
            scanf("%d",&worker[i]);
    }
}node[maxn];
double Len(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
};
struct Dinic
{
    int head[maxn],cur[maxn],d[maxn],S,T,n,nEdge;
    Edge edges[maxm<<1];
    queue<int>q;
    void Init(int S,int T,int n)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        this->S=S;this->T=T;
        this->n=n;
    }
    void AddEdges(int from,int to,int cap)
    {
        edges[++nEdge]=Edge(to,cap,0,head[from]);
        head[from]=nEdge;
        edges[++nEdge]=Edge(from,0,0,head[to]);
        head[to]=nEdge;
    }
    bool BFS()
    {
        memset(d,0xff,sizeof(d));
        d[S]=0;
        q.push(S);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                Edge e=edges[k];
                if(d[e.to]==-1&&e.cap>e.flow)
                {
                    d[e.to]=d[u]+1;
                    q.push(e.to);
                }
            }
        }
        return d[T]!=-1;
    }
    int DFS(int u,int a)
    {
        if(u==T||a==0) return a;
        int flow=0,f;
        for(int &k=cur[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0)
            {
                edges[k].flow+=f;
                edges[k^1].flow-=f;
                flow+=f;a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int MaxFlow()
    {
        int flow=0;
        while(BFS())
        {
            for(int i=0;i<=n;++i) cur[i]=head[i];
            flow+=DFS(S,inf);
        }
        return flow;
    }
}dinic;
int n,m;
Point ps;
int cal(int xx)
{
    int S=0,T=n*2+1;
    dinic.Init(S,T,T+1);
    int res=0;
    double tmp=0;
    for(int i=0;i<n;++i)
    {
        res+=node[i].worker[xx];
        tmp=Len(ps,node[i].pos);
        if(dcmp(tmp-node[i].s)<=0)
        {
            dinic.AddEdges(S,i+1,node[i].worker[xx]);
            dinic.AddEdges(i+n+1,T,node[i].worker[xx]);
        }
    }
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            if(i==j) continue;
            tmp=Len(node[i].pos,node[j].pos);
            if(dcmp(node[i].s+node[i].t+tmp-node[j].s)<=0)
                dinic.AddEdges(i+1,j+n+1,inf);
        }
    res-=dinic.MaxFlow();
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        scanf("%lf%lf",&ps.x,&ps.y);
        n--;
        for(int i=0;i<n;++i)
            node[i].read(m);
        int ans=0;
        for(int i=0;i<m;++i)
            ans+=cal(i);
        printf("%d\n",ans);
    }
    return 0;
}
