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
const int maxn=3000+10;
struct Edge
{
    int v;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int way[maxn][maxn],dis[maxn],pa[maxn],dp[maxn][maxn];
bool vis[maxn];
int n,m;
void clearAll()
{
    memset(vis,0,sizeof(vis));
    memset(head,0xff,sizeof(head));
    for(int i=0;i<n;++i)
       for(int j=0;j<n;++j)
         dp[i][j]=way[i][j]=inf;
    nEdge=-1;
}
void AddEdges(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int prim()
{
    for(int i=0;i<n;++i) {dis[i]=way[0][i];pa[i]=0;}
    dis[0]=0;vis[0]=true;pa[0]=-1;
    int res=0;
    int minnum,pos;
    for(int i=1;i<n;++i)
    {
        minnum=inf;
        for(int j=0;j<n;++j)
        {
            if(!vis[j]&&dis[j]<minnum)
            {
                minnum=dis[j];
                pos=j;
            }
        }
        res+=minnum;
        vis[pos]=true;
        if(pa[pos]!=-1)
        {
            AddEdges(pos,pa[pos]);
            AddEdges(pa[pos],pos);
        }
        for(int k=0;k<n;++k)
        {
            if(!vis[k]&&way[pos][k]<dis[k])
            {
                dis[k]=way[pos][k];
                pa[k]=pos;
            }
        }
    }
    return res;
}
int dfs(int u,int fa,int p)
{
    int ans=inf;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        int tmp=dfs(v,u,p);
        ans=min(ans,tmp);
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    if(fa!=p)
       ans=min(ans,way[u][p]);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a,b,c;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        clearAll();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            way[a][b]=way[b][a]=c;
        }
        double sum=0;
        int val=prim();
        for(int i=0;i<n;++i)
           dfs(i,-1,i);
        int q;
        scanf("%d",&q);
        for(int i=0;i<q;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            if(pa[a]!=b&&pa[b]!=a)
                sum+=val;
            else
                sum+=min(dp[a][b],c)+val-way[a][b];
        }
        printf("%.4lf\n",sum/q);
    }
    return 0;
}
