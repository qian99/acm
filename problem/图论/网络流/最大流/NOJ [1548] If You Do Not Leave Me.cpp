
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
const int maxn=50000+10;
const int maxm=1000000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){};
    Edge(int tt,int cc,int ff,int nn) {to=tt;cap=cc;flow=ff;next=nn;}
}edges[maxm<<1];
int head[maxn],d[maxn],cur[maxn],nEdge;
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
    int f,flow=0;
    for(int& k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            a-=f;
            flow+=f;
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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int A=n*m,B=A+n*110*2,C=B+110*m;
        int S=0,T=C+1;
        int s,p,tmp,maxt=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&s,&p);
            maxt=max(maxt,s);
            for(int j=s;j<s+k;++j)
                AddEdges(A+(i-1)*110*2+j*2-1,A+(i-1)*110*2+j*2,1);
            for(int j=1;j<=p;++j)
            {
                scanf("%d",&tmp);
                AddEdges(S,(i-1)*m+tmp,1);
                for(int l=0;l<k;++l)
                {
                    AddEdges((i-1)*m+tmp,A+(i-1)*110*2+(s+l)*2-1,1);
                    AddEdges(A+(i-1)*110*2+(s+l)*2,B+(s+l-1)*m+tmp,1);
                }
            }
        }
        maxt=maxt+k-1;
        for(int i=1;i<=maxt;++i)
            for(int j=1;j<=m;++j)
                AddEdges(B+(i-1)*m+j,T,1);
        int ans=Maxflow(S,T);
        if(ans==0)
            printf("If you do not leave me, I will by your side until the life end!\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}

