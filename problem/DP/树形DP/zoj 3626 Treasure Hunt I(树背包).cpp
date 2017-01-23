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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],dp[maxn][maxn<<1],val[maxn],nEdge;
int n,m;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    for(int i=0;i<=m;++i) dp[u][i]=val[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        for(int j=m;j>=0;--j)
        {
            for(int i=j;i>=edges[k].w*2;--i)
            {
                dp[u][j]=max(dp[u][j],dp[u][j-i]+dp[v][i-edges[k].w*2]);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        int u,v,w,k;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        scanf("%d%d",&k,&m);
        dfs(k,-1);
        int ans=0;
        for(int i=0;i<=m;++i)
            ans=max(ans,dp[k][m]);
        printf("%d\n",ans);
    }
    return 0;
}
