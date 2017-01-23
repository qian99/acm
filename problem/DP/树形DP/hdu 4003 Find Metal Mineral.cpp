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
    int w;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],dp[maxn][15],nEdge,n,s,k;
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
    for(int i=0;i<=k;++i) dp[u][i]=0;
    for(int p=head[u];p!=-1;p=edges[p].next)
    {
        int v=edges[p].v;
        if(v==fa) continue;
        dfs(v,u);
    }
    for(int p=head[u];p!=-1;p=edges[p].next)
    {
        int v=edges[p].v;
        if(v==fa) continue;
        for(int i=k;i>=0;--i)
        {
            dp[u][i]+=dp[v][0]+2*edges[p].w;
            for(int j=1;j<=i;++j)
                dp[u][i]=min(dp[u][i],dp[v][j]+dp[u][i-j]+j*edges[p].w);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&s,&k))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int a,b,c;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdge(a,b,c);
            AddEdge(b,a,c);
        }
        dfs(s,-1);
        printf("%d\n",dp[s][k]);
    }
    return 0;
}
