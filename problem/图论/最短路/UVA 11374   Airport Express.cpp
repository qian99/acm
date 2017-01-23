#include <iostream>
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
const int maxn=500+10;
struct Edge
{
    int from,to,dist;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode a) const
    {
        return d>a.d;
    }
};
int n,m;
vector<Edge>edges;
vector<int>G[maxn];
int dis1[maxn],dis2[maxn],p1[maxn],p2[maxn];
bool vis[maxn];
void Init()
{
    for(int i=0;i<n;++i)
      G[i].clear();
    edges.clear();
}
void addEdges(int from,int to,int dist)
{
    edges.push_back((Edge){from,to,dist});
    int temp=edges.size();
    G[from].push_back(temp-1);
}
void dijkstra(int s,int *dis,int *p)
{
    priority_queue<HeapNode>q;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;++i)
       dis[i]=inf;
    dis[s]=0;
    q.push((HeapNode){0,s});
    while(!q.empty())
    {
        HeapNode hp=q.top();q.pop();
        int u=hp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            Edge e=edges[G[u][i]];
            if(dis[e.to]>dis[u]+e.dist)
            {
                dis[e.to]=dis[u]+e.dist;
                p[e.to]=G[u][i];
                q.push((HeapNode){dis[e.to],e.to});
            }
        }
    }
}
void printA(int k,int s)
{
    if(k==s)
    {
        printf("%d",k+1);
        return;
    }
    int t=p1[k];
    Edge e=edges[t];
    printA(e.from,s);
    printf(" %d",k+1);
}
void printB(int k,int e)
{
    if(k==e)
    {
        printf(" %d",k+1);
        return;
    }
    printf(" %d",k+1);
    int t=p2[k];
    Edge x=edges[t];
    printB(x.from,e);
}
void slove(int s,int e,int st,int et)
{
    if(st==-1&&et==-1)
    {
        printA(e,s);
        printf("\nTicket Not Used\n");
    }
    else
    {
        printA(st,s);
        printB(et,e);
        printf("\n%d\n",st+1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int s,e;
    int tcase=0;
    while(~scanf("%d%d%d",&n,&s,&e))
    {
        if(tcase>0) printf("\n");
        tcase++;
        s--;e--;
        Init();
        scanf("%d",&m);
        int a,b,c,k;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            addEdges(a,b,c);
            addEdges(b,a,c);
        }
        memset(p1,0,sizeof(p1));
        memset(p2,0,sizeof(p2));
        dijkstra(s,dis1,p1);
        dijkstra(e,dis2,p2);
        int minlen=dis1[e];
        int st=-1,et=-1;
        scanf("%d",&k);
        for(int i=0;i<k;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            if(dis1[a]+dis2[b]+c<minlen)
            {
                minlen=dis1[a]+dis2[b]+c;
                st=a;
                et=b;
            }
            if(dis1[b]+dis2[a]+c<minlen)
            {
                minlen=dis1[b]+dis2[a]+c;
                st=b;
                et=a;
            }
        }
        slove(s,e,st,et);
        printf("%d\n",minlen);
    }
    return 0;
}
