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
const int maxn=1000+100;
const int maxm=10000+1000;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
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
        for(int i=0;i<=t;++i) cur[i]=head[i];
        flow+=DFS(s,inf,t);
    }
    return flow;
}
char a[55][55],b[55][55];
double dist(int x1,int y1,int x2,int y2)
{
    return sqrt((double)(x1-x2)*(x1-x2)+(double)(y1-y2)*(y1-y2));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n,m,d;
        scanf("%d%d",&n,&d);
        for(int i=1;i<=n;++i)
            scanf("%s",a[i]);
        for(int i=1;i<=n;++i)
            scanf("%s",b[i]);
        m=strlen(a[1]);
        for(int i=1;i<=n;++i)
            for(int j=m;j>=1;j--)
            {
                a[i][j]=a[i][j-1];
                b[i][j]=b[i][j-1];
            }
        int S=0,T=n*m*2+1,tot=0;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                if(a[i][j]=='0') continue;
                AddEdges((i-1)*m+j,(i-1)*m+j+n*m,a[i][j]-'0');
                if(b[i][j]=='L')
                    {AddEdges(S,(i-1)*m+j,1);tot++;}
                if(i-d<=0||j-d<=0||i+d>=n+1||j+d>=m+1)
                    AddEdges((i-1)*m+j+n*m,T,inf);
                for(int x=1;x<=n;++x)
                    for(int y=1;y<=m;++y)
                    {
                        if(i==x&&j==y) continue;
                        if(a[i][j]=='0') continue;
                        if(dist(i,j,x,y)<=d)
                            AddEdges((i-1)*m+j+n*m,(x-1)*m+y,inf);
                    }
            }
        }
        int ans=tot-MaxFlow(S,T);
        printf("Case #%d: ",tcase);
        if(ans==0)
            printf("no lizard was left behind.\n");
        else if(ans==1)
            printf("%d lizard was left behind.\n",ans);
        else
            printf("%d lizards were left behind.\n",ans);
    }
    return 0;
}
