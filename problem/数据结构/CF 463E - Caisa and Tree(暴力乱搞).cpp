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
const int maxn = 100000 + 10;
const int maxm = 2000000 + 10;
int primes[maxm],min_div[maxm],pcnt;
bool flag[maxm];
vector<int>pos[maxm];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt = 0;
    for(int i = 2;i < maxm;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++] = i;
            min_div[i] = i;
        }
        for(int j = 0;j < pcnt;++j)
        {
            if(i*primes[j] > maxm) break;
            flag[i*primes[j]] = true;
            min_div[i*primes[j]] = primes[j];
            if(i % primes[j] == 0) break;
        }
    }
}
int ans[maxn],val[maxn],d[maxn];
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
void dfs(int u,int fa)
{
    ans[u] = -1;
    int v,x,size;
    x = val[u];
    while(x > 1)
    {
        int p = min_div[x];
        size = pos[p].size();
        if(size)
        {
            v = pos[p][size-1];
            if(ans[u] == -1) ans[u] = v;
            else if(d[v] > d[ans[u]]) ans[u] = v;
        }
        pos[p].push_back(u);
        while(x%p == 0) x /= p;
    }
    for(int k = head[u];k != -1; k = edges[k].next)
    {
        v = edges[k].v;
        if(v == fa) continue;
        d[v] = d[u] + 1;
        dfs(v,u);
    }
    x = val[u];
    while(x > 1)
    {
        int p = min_div[x];
        pos[p].pop_back();
        while(x%p == 0) x /= p;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    getprimes();
    int n, q;
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    scanf("%d%d",&n,&q);
    for(int i = 1;i <= n;++i)
        scanf("%d",&val[i]);
    int u,v;
    for(int i = 1;i < n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    d[1] = 0;
    dfs(1,-1);
    int type;
    while(q--)
    {
        scanf("%d%d",&type,&u);
        if(type == 1)
        {
            printf("%d\n",ans[u]);
        }
        else
        {
            scanf("%d",&v);
            val[u] = v;
            d[1] = 0;
            dfs(1,-1);
        }
    }
    return 0;
}
