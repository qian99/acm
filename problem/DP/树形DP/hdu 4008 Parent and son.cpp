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
const int maxn=100000+10;
struct Edge
{
    int v;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int dp[maxn][2],dir[maxn],mifa[maxn],pre[maxn],post[maxn],dfs_clock;
int dp2[maxn][2],dir2[maxn],mifa2[maxn];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0]=dp[u][1]=inf;
    dp2[u][0]=dp2[u][1]=inf;
    pre[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        int tmp=min(v,dp[v][0]);
        if(tmp<dp[u][0])
        {
            dp[u][1]=dp[u][0];
            dp[u][0]=tmp;
            dir[u]=v;
        }
        else if(tmp<dp[u][1]) dp[u][1]=tmp;
        if(v<dp2[u][0])
        {
            dp2[u][1]=dp2[u][0];
            dp2[u][0]=v;
            dir2[u]=v;
        }
        else if(v<dp2[u][1]) dp2[u][1]=v;
    }
    post[u]=++dfs_clock;
}
void dfs2(int u,int fa,int mf)
{
    mifa[u]=mf;
    mifa2[u]=(fa==-1)?inf:fa;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(dir[u]==v) dfs2(v,u,min(u,min(mf,dp[u][1])));
        else dfs2(v,u,min(u,min(mf,dp[u][0])));
    }
}
void solve(int x,int y,int &ans1,int &ans2)
{
    if(x==y)
    {
        ans1=min(dp[x][0],mifa[x]);
        ans2=min(dp2[x][0],mifa2[x]);
        return;
    }
    if(pre[y]<pre[x]&&post[y]>post[x])
    {
        int z=dir[y];
        if(z==x||(pre[z]<pre[x]&&post[z]>post[x]))
           ans1=min(mifa[y],dp[y][1]);
        else ans1=min(mifa[y],dp[y][0]);
        z=dir2[y];
        if(z==x||(pre[z]<pre[x]&&post[z]>post[x]))
           ans2=min(mifa2[y],dp2[y][1]);
        else ans2=min(mifa2[y],dp2[y][0]);
        return;
    }
    ans1=dp[y][0];
    ans2=dp2[y][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        memset(head,0xff,sizeof(head));
        memset(dir,0,sizeof(dir));
        memset(dir2,0,sizeof(dir2));
        nEdge=-1;
        int a,b,x,y;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&a,&b);
            AddEdge(a,b);
            AddEdge(b,a);
        }
        dfs_clock=0;
        dfs(1,-1);
        dfs2(1,-1,inf);
        while(q--)
        {
            scanf("%d%d",&x,&y);
            int ans1,ans2;
            solve(x,y,ans1,ans2);
            if(ans1==inf||ans2==inf) printf("no answers!\n");
            else printf("%d %d\n",ans2,ans1);
        }
        printf("\n");
    }
    return 0;
}
