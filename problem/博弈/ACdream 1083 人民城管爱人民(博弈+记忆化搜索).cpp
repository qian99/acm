#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=100000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],dp[maxn][2],nEdge,n,m;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
}
int f(int u,int st)
{
    if(u==n-1) return 0;
    if(dp[u][st]!=-1) return dp[u][st];
    dp[u][st]=inf;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        dp[u][st]=min(dp[u][st],f(v,st)+edges[k].w);
    }
    if(!st)
    {
        int tmp[2],cost;
        tmp[0]=tmp[1]=inf;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            cost=f(v,st|1)+edges[k].w;
            if(cost<tmp[0])
            {
                tmp[1]=tmp[0];
                tmp[0]=cost;
            }
            else if(cost<tmp[1])
                tmp[1]=cost;
        }
        dp[u][st]=max(dp[u][st],tmp[1]);
    }
    return dp[u][st];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int u,v,w;
        memset(dp,0xff,sizeof(dp));
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        int ans=f(0,0);
        if(ans==inf) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
