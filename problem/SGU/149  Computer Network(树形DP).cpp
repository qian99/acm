#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int dp[maxn][2],fg[maxn],res[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0]=dp[u][1]=0;
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
            fg[u]=v;
        }
        else if(tmp>dp[u][1])
            dp[u][1]=tmp;
    }
}
void dfs2(int u,int fa,int val)
{
    res[u]=max(dp[u][0],val);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(fg[u]==v) dfs2(v,u,max(val,dp[u][1])+edges[k].w);
        else dfs2(v,u,max(val,dp[u][0])+edges[k].w);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int v,w;
    for(int u=2;u<=n;++u)
    {
        scanf("%d%d",&v,&w);
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }
    dfs(1,-1);
    dfs2(1,-1,0);
    for(int i=1;i<=n;++i)
      printf("%d\n",res[i]);
    return 0;
}
