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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 55;
const int maxm = 10000 + 10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm];
int head[maxn],d[maxn],p[maxn],a[maxn],nEdge;
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge] = Edge(to,cap,cost,head[from]);
    head[from] = nEdge;
    edges[++nEdge] = Edge(from,0,-cost,head[to]);
    head[to] = nEdge;
}
int spfa(int S,int T,int & flow,int & cost)
{
    for(int i = 0;i <= T;++i)
    {
        d[i] = inf;
        inq[i] = false;
    }
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
            if(e.cap && d[e.to] > d[u] + edges[k].cost)
            {
                d[e.to] = d[u] + edges[k].cost;
                p[e.to] = k;
                a[e.to] = min(a[u],e.cap);
                if(!inq[e.to]) {inq[e.to] = true;q.push(e.to);}
            }
        }
    }
    if(d[T] == inf) return false;
    flow += a[T];
    cost += a[T]*d[T];
    int u = T;
    while(u != S)
    {
        edges[p[u]].cap -= a[T];
        edges[p[u]^1].cap += a[T];
        u = edges[p[u]^1].to;
    }
    return true;
}
int B[maxn],like[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0,n,m,K;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&K);
        int S = 0,T = n + m + 1,sum = 0;
        for(int i = 1;i <= m;++i)
        {
            scanf("%d",&B[i]);
            sum += B[i];
        }
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        for(int i = 1;i <= m;++i)
        {
            for(int j = 1;j <= n;++j)
            {
                scanf("%d",&like[i][j]);
                if(like[i][j])
                    AddEdges(j,i + n,1,0);
            }
        }
        for(int i = 1;i <= n;++i)
            AddEdges(S,i,1,0);
        for(int i = 1;i <= m;++i)
        {
            if(B[i]/K)
                AddEdges(i + n,T,B[i]/K,-K);
            if(B[i]%K >= 1)
                AddEdges(i + n,T,1,-(B[i]%K));
        }
        int flow = 0,cost = 0;
        while(spfa(S,T,flow,cost));
        int remain = n - flow,need = sum + cost;
        printf("Case #%d: ",++tcase);
        if(remain >= need)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
