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
const int maxn=200000+1000;
const int maxm=1000000+1000;
struct Node
{
    int to,next;
};
int head[maxn],low[maxn],dfsn[maxn],dp[maxn][2];
int n,m,dfs_clock,nEdge,bright;
bool vis[maxm<<1];
Node edge[maxm<<1];

void add_Edge(int u,int v)
{
    edge[nEdge].to=v;
    edge[nEdge].next=head[u];
    head[u]=nEdge;
    nEdge++;
}

void dfs(int u)
{
    low[u]=dfsn[u]=dfs_clock++;
    dp[u][0]=dp[u][1]=0;
    for(int k=head[u];k!=-1;k=edge[k].next)
    {
        if(!vis[k>>1])
        {
            vis[k>>1]=true;
            int v=edge[k].to;
            if(dfsn[v]==-1)
            {
                dfs(v);
                if(low[v]>dfsn[u]) bright++;
                int temp=dp[v][0]+(int)(low[v]>dfsn[u]);
                if(temp>dp[u][0])
                {
                    dp[u][1]=dp[u][0];
                    dp[u][0]=temp;
                }
                else if(temp>dp[u][1])
                {
                    dp[u][1]=temp;
                }
                low[u]=min(low[u],low[v]);
            }
            else
                low[u]=min(low[u],dfsn[v]);

        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int size = 256 << 20; // 256MB
	char *p = (char*)malloc(size) + size;
	__asm__("movl %0, %%esp\n" :: "r"(p) );
    //int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        bright=dfs_clock=nEdge=0;
        memset(head,0xff,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dfsn,0xff,sizeof(dfsn));
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            add_Edge(a-1,b-1);
            add_Edge(b-1,a-1);
        }
        dfs(0);
        int temp=0;
        for(int i=0;i<n;++i)
        {
            temp=max(temp,dp[i][0]+dp[i][1]);
        }
        printf("%d\n",bright-temp);
    }
    return 0;
}
