#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int maxn=20000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxn<<1];
int head[maxn],degree[maxn],nEdge,n;
int dp[maxn],cnt[maxn],maxval,val[maxn],p;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u]=val[u];
    cnt[u]=1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        if(dp[v]>0)
        {
            dp[u]+=dp[v];
            cnt[u]+=dp[v];
        }
    }
    if(dp[u]>maxval)
    {
        maxval=dp[u];
        p=cnt[u];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    memset(head,0xff,sizeof(head));
    memset(degree,0,sizeof(degree));
    nEdge=-1;
    for(int i=1;i<=n;++i)
      scanf("%d",&val[i]);
    int u,v;
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        degree[u]++;degree[v]++;
        AddEdge(u,v);
        AddEdge(v,u);
    }
    maxval=-inf;
    dfs(1,-1);
    if(p==n)
    {
        int dec=inf;
        for(int i=1;i<=n;++i)
          if(degree[i]==1) dec=min(dec,val[i]);
        maxval-=dec;
    }
    printf("%d\n",maxval);
    return 0;
}
