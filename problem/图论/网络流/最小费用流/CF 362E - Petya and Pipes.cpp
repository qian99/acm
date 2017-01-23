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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 55;
const int maxm = 10000 + 10;
struct Edge
{
    int to,cap,cost,next;
    Edge(int to = 0,int cap = 0,int cost = 0,int next = 0):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],a[maxn],p[maxn],MaxK;
int inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge] = Edge(to,cap,cost,head[from]);
    head[from] = nEdge;
    edges[++nEdge] = Edge(from,0,-cost,head[to]);
    head[to] = nEdge;
}
bool spfa(int S,int T,int &flow,int & cost)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[S] = 0;a[S] = inf;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        inq[u] = false;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            Edge e = edges[k];
            if(e.cap && d[e.to] > d[u] + e.cost)
            {
                d[e.to] = d[u] + e.cost;
                a[e.to] = min(a[u],e.cap);
                p[e.to] = k;
                if(!inq[e.to]) {inq[e.to] = true;q.push(e.to);}
            }
        }
    }
    if(d[T] == inf || cost + d[T] > MaxK) return false;
    int num;
    if(d[T] == 0) num = a[T];
    else num = (MaxK - cost)/d[T];
    num = min(num,a[T]);
    flow += num;
    cost += num*d[T];
    int u = T;
    while(u != S)
    {
        edges[p[u]].cap -= num;
        edges[p[u]^1].cap += num;
        u = edges[p[u]^1].to;
    }
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d%d",&n,&MaxK);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    for(int i = 1;i <= n;++i)
    {
        int w;
        for(int j = 1;j <= n;++j)
        {
            scanf("%d",&w);
            if(w)
            {
                AddEdges(i,j,w,0);
                AddEdges(i,j,inf,1);
            }
        }
    }
    int flow = 0,cost = 0;
    while(spfa(1,n,flow,cost));
    printf("%d\n",flow);
    return 0;
}
