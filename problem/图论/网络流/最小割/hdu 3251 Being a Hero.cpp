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
const int maxm=200000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
bool vis[maxn];
vector<int>cut;
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
            Edge &e=edges[k];
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
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        Edge &e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) return flow;
        }
    }
    d[u]=-1;
    return flow;
}
void findcut(int S,int T,int m)
{
    cut.clear();
    memset(vis,0,sizeof(vis));
    queue<int>q;
    q.push(S);
    vis[S]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
//    for(int i=0;i<m;++i)
//    {
//        int k=i<<1;
//        if(vis[edges[k^1].to]&&!vis[edges[k].to])
//            cut.push_back(i+1);
//    }
    for(int u=1;u<T;++u)
        if(vis[u])
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            if(k&1) continue;
            Edge &e=edges[k];
            if(!vis[e.to]&&e.to!=T)
                cut.push_back(k/2+1);
        }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m,k,S,T;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d%d%d",&n,&m,&k);
        S=1,T=n+1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        int sum=0;
        while(k--)
        {
            scanf("%d%d",&u,&w);
            AddEdges(u,T,w);
            sum+=w;
        }
        int flow=0;
        while(BFS(S,T))
            flow+=DFS(S,inf,T);
        findcut(S,T,m);
        printf("Case %d: %d\n",tcase,sum-flow);
//        sort(cut.begin(),cut.end());
        int size=cut.size();
        printf("%d",size);
        for(int i=0;i<size;++i)
            printf(" %d",cut[i]);
        printf("\n");
    }
    return 0;
}
