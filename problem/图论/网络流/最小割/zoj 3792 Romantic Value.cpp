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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=55;
const int maxm=10000+10;
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,head[to]);
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
            if(d[e.to]==-1&&e.cap)
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
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap),t))>0)
        {
            edges[k].cap-=f;
            edges[k^1].cap+=f;
            flow+=f;a-=f;
            if(a==0) return flow;
        }
    }
    d[u]=-1;
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n,m,s,t;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&n,&m,&s,&t);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        int sum=0;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w*10000+1);
            AddEdges(v,u,w*10000+1);
            sum+=w;
        }
        int flow=0;
        while(BFS(s,t))
            flow+=DFS(s,inf,t);
        if(flow==0) puts("Inf");
        else
        {
            int ans=flow/10000;
            int ans2=flow%10000;
            double res=(double)(sum-ans)/ans2;
            printf("%.2lf\n",res);
        }
    }
    return 0;
}