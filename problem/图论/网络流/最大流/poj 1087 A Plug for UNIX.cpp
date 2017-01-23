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
const int maxn=512;
const int maxm=100000+10;
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
            Edge &e=edges[k];
            if(e.cap&&d[e.to]==-1)
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
string rec[110],devices[110][2],adapter[110][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(cin>>n)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            cin>>rec[i];
        cin>>m;
        for(int i=1;i<=m;++i)
            cin>>devices[i][0]>>devices[i][1];
        cin>>k;
        for(int i=1;i<=k;++i)
            cin>>adapter[i][0]>>adapter[i][1];
        int S=0,T=n+m+k+1;
        for(int i=1;i<=n;++i)
            AddEdges(i,T,1);
        for(int i=1;i<=m;++i)
        {
            AddEdges(S,i+n,1);
            for(int j=1;j<=n;++j)
                if(devices[i][1]==rec[j])
                    AddEdges(i+n,j,1);
            for(int j=1;j<=k;++j)
                if(devices[i][1]==adapter[j][0])
                    AddEdges(i+n,j+n+m,1);
        }
        for(int i=1;i<=k;++i)
        {
            for(int j=1;j<=n;++j)
                if(adapter[i][1]==rec[j])
                    AddEdges(i+n+m,j,inf);
            for(int j=1;j<=k;++j)
                if(adapter[i][1]==adapter[j][0])
                    AddEdges(i+n+m,j+n+m,inf);
        }
        int flow=0;
        while(BFS(S,T))
            flow+=DFS(S,inf,T);
        cout<<m-flow<<endl;
    }
    return 0;
}
