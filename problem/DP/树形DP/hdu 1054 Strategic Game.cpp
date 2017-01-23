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
    int v;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],dp[maxn][2],nEdge;
bool vis[maxn][2];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int dfs(int u,int fa,int p)
{
    if(vis[u][p]) return dp[u][p];
    vis[u][p]=true;
    dp[u][p]=p;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(p) dp[u][p]+=min(dfs(v,u,p),dfs(v,u,p^1));
        else dp[u][p]+=dfs(v,u,p^1);
    }
    return dp[u][p];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        memset(vis,0,sizeof(vis));
        nEdge=-1;
        int a,b,k;
        for(int i=0;i<n;++i)
        {
            scanf("%d:(%d)",&a,&k);
            while(k--)
            {
                scanf("%d",&b);
                AddEdge(a,b);
                AddEdge(b,a);
            }
        }
        printf("%d\n",min(dfs(1,-1,0),dfs(1,-1,1)));
    }
    return 0;
}
