#include<iostream>
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
typedef long long ll;
const int maxn=1000+10;
const int maxm=100000+10;
const double sp=400.0;
const double tp=789.0;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],cur[maxn],d[maxn],nEdge,n;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int s,int t)
{
    memset(d,0xff,sizeof(d));
    d[s]=0;
    queue<int>q;
    q.push(s);
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
    return d[t]!=-1;
}
int DFS(int u,int a,int t)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e =edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int MaxFlow(int s,int t)
{
    int flow=0;
    while(BFS(s,t))
    {
        for(int i=0;i<=n*2+1;++i) cur[i]=head[i];
        flow+=DFS(s,inf,t);
    }
    return flow;
}
struct Point
{
    double f,x,y,r;
    void read()
    {
        scanf("%lf%lf%lf%lf",&f,&x,&y,&r);
    }
}point[maxn];
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
double Dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool check(Point a,Point b)
{
    double d=Dis(a,b);
    return dcmp(d-a.r-b.r)<=0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S,T;
        for(int i=1;i<=n;++i)
        {
            point[i].read();
            if(dcmp(point[i].f-sp)==0) S=i;
            else if(dcmp(point[i].f-tp)==0) T=i;
        }
        int tmp;
        for(int i=1;i<=n;++i)
        {
            if(i==S) AddEdges(i,i+n,inf);
            else AddEdges(i,i+n,1);
            for(int j=1;j<=n;++j)
            {
                if(i==j) continue;
                if(!check(point[i],point[j])) continue;
                tmp=dcmp(point[i].f-point[j].f);
                if(tmp<0)
                    AddEdges(i+n,j,1);
            }
        }
        int ans=MaxFlow(S,T);
        if(ans>=2||check(point[S],point[T]))
            printf("Game is VALID\n");
        else
            printf("Game is NOT VALID\n");

    }
    return 0;
}
