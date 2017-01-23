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
const int maxn=200+50;
const int maxm=200000+10;
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
    queue<int>q;
    q.push(s);
    d[s]=0;
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
        Edge e=edges[k];
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
    double x,y,z;
    void read()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
}pt[maxn];
int F[maxn],L[maxn];
double Dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
bool test(double R)
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int S=n*2+1,T=1,sum=0;
    double tmp;
    for(int i=2;i<=n;++i)
    {
        AddEdges(i,i+n,L[i]);
        AddEdges(S,i,F[i]);
        sum+=F[i];
        tmp=Dis(pt[1],pt[i]);
        if(dcmp(R-tmp)>=0)
            AddEdges(i+n,T,inf);
    }
    for(int i=2;i<=n;++i)
        for(int j=i+1;j<=n;++j)
        {
            tmp=Dis(pt[i],pt[j]);
            if(dcmp(R-tmp)>=0)
            {
                AddEdges(i+n,j,inf);
                AddEdges(j+n,i,inf);
            }
        }
    int ans=MaxFlow(S,T);
    return ans==sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
        {
            pt[i].read();
            scanf("%d%d",&F[i],&L[i]);
        }
        double L=0,R=40000,m;
        if(!test(R))
            printf("-1\n");
        else
        {
            while(R-L>1e-8)
            {
                m=(L+R)/2;
                if(test(m))
                    R=m;
                else
                    L=m;
            }
            printf("%.7lf\n",L);
        }
    }
    return 0;
}
