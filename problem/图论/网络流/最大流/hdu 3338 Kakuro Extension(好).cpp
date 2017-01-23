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
const int maxn=20000+10;
const int maxm=200000+10;
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
            a-=f;flow+=f;
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
struct Node
{
    int id,type,vx,vy;
    Node(){};
    Node(int id,int type,int vx,int vy):id(id),type(type),vx(vx),vy(vy){}
}node[111][111];
char str[11];
int indx[111][111];
Node NewNode(const char *str,int id)
{
    if(str[3]=='.') return Node(id,0,-1,-1);
    if(str[3]=='X') return Node(id,2,-1,-1);
    int x=-1,y=-1;
    if(str[4]!='X') x=(str[6]-'0')+(str[5]-'0')*10+(str[4]-'0')*100;
    if(str[0]!='X') y=(str[2]-'0')+(str[1]-'0')*10+(str[0]-'0')*100;
    return Node(id,1,x,y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                scanf("%s",str);
                node[i][j]=NewNode(str,i*m+j+1);
            }
        int S=0,T=n*m+n*m+1;
        for(int i=0;i<n;++i)
        {
            int j=0;
            for(;j<m;++j)
            {
                if(node[i][j].type==1&&node[i][j].vx!=-1)
                {
                    int k=0;
                    while(k+j+1<m&&node[i][k+j+1].type==0) k++;
                    AddEdges(S,node[i][j].id,node[i][j].vx-k);
                    for(int l=1;l<=k;++l)
                        AddEdges(node[i][j].id,node[i][j+l].id,8);
                    j+=k;
                }
            }
        }
        for(int j=0;j<m;++j)
        {
            int i=0;
            for(;i<n;++i)
            {
                if(node[i][j].type==1&&node[i][j].vy!=-1)
                {
                    int k=0;
                    while(k+i+1<n&&node[i+k+1][j].type==0) k++;
                    AddEdges(node[i][j].id+n*m,T,node[i][j].vy-k);
                    for(int l=1;l<=k;++l)
                    {
                        AddEdges(node[i+l][j].id,node[i][j].id+n*m,8);
                        indx[i+l][j]=nEdge-1;
                    }
                    i+=k;
                }
            }
        }
        MaxFlow(S,T);
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                if(j) printf(" ");
                if(node[i][j].type) printf("_");
                else printf("%d",edges[indx[i][j]].flow+1);
            }
            printf("\n");
        }
    }
    return 0;
}
