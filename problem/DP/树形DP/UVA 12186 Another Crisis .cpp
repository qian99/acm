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
const int maxn = 100000+10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int dp[maxn],S[maxn],T,n;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
void dfs(int u)
{
    dp[u] = 1;
    int tot = 0;
    for(int k = head[u]; k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        dfs(v);
    }
    for(int k = head[u]; k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        S[tot++] = dp[v];
    }
    if(tot)
    {
        int num = tot*T/100;
        if((double)num/tot < T/100.0) num++;
        sort(S,S + tot);
        dp[u] = 0;
        for(int i = 0;i < num;++i)
            dp[u] += S[i];
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&T))
    {
        if(n == 0 && T == 0) break;
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        int u;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&u);
            AddEdges(u,i);
        }
        dfs(0);
        printf("%d\n",dp[0]);
    }
    return 0;
}
