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
const int maxn = 400 + 10;
const int maxm = 200000 + 10;
struct Edge
{
    int to,cap,cost,next;
    Edge(int to = 0,int cap = 0,int cost = 0,int next = 0):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],p[maxn],a[maxn],nEdge;
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge] = Edge(to,cap,cost,head[from]);
    head[from] = nEdge;
    edges[++nEdge] = Edge(from,0,-cost,head[to]);
    head[to] = nEdge;
}
bool spfa(int S,int T,int & flow,int & cost)
{
    for(int i = 0;i <= T;++i)
    {
        d[i] = inf;
        inq[i] = false;
    }
    a[S] = inf;p[S] = 0;
    d[S] = 0;
    queue<int>q;
    q.push(S);
    while(!q.empty())
    {
        int u = q.front();q.pop();
        inq[u] = false;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            Edge e = edges[k];
            if(d[e.to] > d[u] + e.cost && e.cap)
            {
                d[e.to] = d[u] + e.cost;
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
string names[222];
int cal(int x,int y)
{
    if(x == y) return 0;
    int n = names[x].length();
    int m = names[y].length();
    int k = min(n,m);
    int res = 0;
    for(int i = 0;i < k;++i)
    {
        if(names[x][n - i - 1] != names[y][i])
            return res;
        res++;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        for(int i = 1;i <= n;++i)
            cin>>names[i];
        int S = 0,T = n*2 + 1;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
            {
                int val = cal(i,j);
                AddEdges(i,j + n,1,-val);
            }
        for(int i = 1;i <= n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i + n,T,1,0);
        }
        int flow = 0,cost = 0;
        while(spfa(S,T,flow,cost));
        cout<<(-cost)<<endl;
    }
    return 0;
}

