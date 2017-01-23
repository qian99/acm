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
typedef long long ll;
const int maxn=10000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],dp[maxn][2],nEdge;
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(dp,0,sizeof(dp));
    nEdge=-1;
}
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        int tmp=dp[v][0]+edges[k].w;
        if(tmp>dp[u][0])
        {
            dp[u][1]=dp[u][0];
            dp[u][0]=tmp;
        }
        else if(tmp>dp[u][1])
            dp[u][1]=tmp;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n=0,u,v,w;
    Init();
    while(~scanf("%d%d%d",&u,&v,&w))
    {
        AddEdges(u,v,w);
        n=max(n,u);
        n=max(n,v);
    }
    dfs(1,-1);
    int ans=0;
    for(int i=1;i<=n;++i)
        ans=max(ans,dp[i][0]+dp[i][1]);
    printf("%d\n",ans);
    return 0;
}
