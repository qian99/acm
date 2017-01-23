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
const int maxn=5555;
const int maxm=100000+10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
struct Edge
{
    int to,cap,next;
    Edge(){}
    Edge(int to,int cap,int next):to(to),cap(cap),next(next){}
}edges[maxm];
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
int A[55][55],B[55][55],id[55][55];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m,g,s,S,T;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d%d%d",&n,&m,&g,&s);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int cnt=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                scanf("%d",&A[i][j]);
                id[i][j]=++cnt;
            }
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                scanf("%d",&B[i][j]);
        S=0,T=n*m*2+1;
        int x,y,sum=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                sum+=A[i][j]+B[i][j];
                AddEdges(id[i][j],id[i][j]+n*m,inf);
                if((i+j)&1)
                {
                    AddEdges(S,id[i][j],A[i][j]);
                    AddEdges(id[i][j]+n*m,T,B[i][j]);
                }
                else
                {
                    AddEdges(S,id[i][j],B[i][j]);
                    AddEdges(id[i][j]+n*m,T,A[i][j]);
                }
                for(int k=0;k<4;++k)
                {
                    x=i+dirx[k];
                    y=j+diry[k];
                    if(x>=0&&x<n&&y>=0&&y<m)
                    {
                        if((i+j)&1)  AddEdges(id[i][j],id[x][y]+n*m,g);
                        else AddEdges(id[i][j],id[x][y]+n*m,s);
                    }
                }
            }
        int flow=0;
        while(BFS(S,T))
            flow+=DFS(S,inf,T);
        printf("Case %d: %d\n",tcase,sum-flow);
    }
    return 0;
}
