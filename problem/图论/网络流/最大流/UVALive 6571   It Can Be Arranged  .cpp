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
const int maxn=200+10;
const int maxm=20000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],cur[maxn],d[maxn],nEdge;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int s,int t)
{
    queue<int>q;
    memset(d,0xff,sizeof(d));
    d[s]=0;
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
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow(int s,int t)
{
    int flow=0;
    while(BFS(s,t))
    {
        for(int i=0;i<=t;++i) cur[i]=head[i];
        flow+=DFS(s,inf,t);
    }
    return flow;
}
int A[maxn],B[maxn],C[maxn];
int clean[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int S=0,T=2*n+1,sum=0;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&A[i],&B[i],&C[i]);
            C[i]--;C[i]/=m;C[i]++;
            sum+=C[i];
            AddEdges(S,i,C[i]);
            AddEdges(i+n,T,C[i]);
        }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&clean[i][j]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            {
                if(i!=j&&B[i]+clean[i][j]<A[j])
                    AddEdges(i,j+n,inf);
            }
        sum-=Maxflow(S,T);
        printf("Case %d: %d\n",++tcase,sum);
    }
    return 0;
}
