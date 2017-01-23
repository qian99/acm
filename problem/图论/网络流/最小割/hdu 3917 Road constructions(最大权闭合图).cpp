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
const int maxn = 5000 + 10;
const int maxm = 500000 + 10;
struct Edge
{
    int to,cap,next;
    Edge(int to = 0,int cap = 0,int next = 0):to(to),cap(cap),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],nEdge;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge] = Edge(to,cap,head[from]);
    head[from] = nEdge;
    edges[++nEdge] = Edge(from,0,head[to]);
    head[to] = nEdge;
}
bool BFS(int S,int T)
{
    for(int i = 0;i <= T;++i)
        d[i] = -1;
    d[S] = 0;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            Edge e = edges[k];
            if(e.cap && d[e.to] == -1)
            {
                d[e.to] = d[u] + 1;
                q.push(e.to);
            }
        }
    }
    return d[T] != -1;
}
int DFS(int u,int a,int T)
{
    if(u == T || a == 0) return a;
    int flow = 0,f;
    for(int k = head[u];k != -1; k = edges[k].next)
    {
        Edge e = edges[k];
        if(d[e.to] == d[u] + 1 && (f = DFS(e.to,min(a,e.cap),T)) > 0)
        {
            edges[k].cap -= f;
            edges[k^1].cap += f;
            flow += f;
            a -= f;
            if(a == 0) return flow;
        }
    }
    d[u] = -1;
    return flow;
}
int tax[maxn];
vector<int>sv[1010],st[1010];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int S = 0,T = m + 1;
        for(int i = 1;i <= m;++i)
            scanf("%d",&tax[i]);
        for(int i = 0;i <= n;++i)
        {
            sv[i].clear();
            st[i].clear();
        }
        int k,u,v,x,cost;
        scanf("%d",&k);
        for(int i = 0;i < k;++i)
        {
            scanf("%d%d%d%d",&u,&v,&x,&cost);
            sv[u].push_back(x);
            st[v].push_back(x);
            tax[x] -= cost;
        }
        int sum = 0;
        for(int i = 1;i <= m;++i)
        {
            if(tax[i] > 0) sum += tax[i];
            if(tax[i] < 0)
                AddEdges(i,T,-tax[i]);
            else if(tax[i] > 0)
                AddEdges(S,i,tax[i]);
        }
        for(int i = 1;i <= n;++i)
        {
            for(int j = 0;j < (int)st[i].size();++j)
                for(int k = 0;k < (int)sv[i].size();++k)
                {
                    u = st[i][j];
                    v = sv[i][k];
                    AddEdges(u,v,inf);
                }
        }
        int flow = 0;
        while(BFS(S,T))
            flow += DFS(S,inf,T);
        sum -= flow;
        printf("%d\n",sum);
    }
    return 0;
}
