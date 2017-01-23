//dp[i][j][k],i的子树，已经安排了j个市场，此时i去市场k的最大人数
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
const int maxn=200+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
int dp[maxn][maxn][maxn],flag[maxn],childs[maxn];
int maxv[maxn][maxn],dp2[maxn][maxn],id[maxn];
int head[maxn],g[maxn][maxn],nEdge;
int n,m;
pair<int,int> premart[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(flag,0,sizeof(flag));
    memset(g,0x3f,sizeof(g));
    for(int i=0;i<=n;++i) g[i][i]=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            for(int k=0;k<=n;++k)
                dp[i][j][k]=-inf;
}
void floyd()
{
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
void getpremart()
{
    for(int i=1;i<=n;++i)
    {
        pair<int,int> pii=make_pair(inf,0);
        for(int j=1;j<=n;++j)
            if(flag[j]) pii=min(pii,make_pair(g[i][j],j));
        premart[i]=pii;
    }
}
inline void Update(int &a,int b)
{
    if(b>a) a=b;
}
void dfs(int u,int fa)
{
    childs[u]=1;
    int tot=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        childs[u]+=childs[v];
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        id[++tot]=v;
        for(int i=0;i<=m;++i)
        {
            maxv[tot][i]=-inf;
            for(int j=1;j<=n;++j)
                maxv[tot][i]=max(maxv[tot][i],dp[v][i][j]);
        }
    }
    for(int belong=1;belong<=n;++belong)
    {
        if(make_pair(g[u][belong],belong)<=premart[u])
        {
            if(flag[belong])
            {
                for(int i=0;i<=tot;++i)
                    for(int j=0;j<=m;++j)
                        dp2[i][j]=-inf;
                dp2[0][0]=0;
                int cnow=0;
                for(int i=0;i<tot;++i)
                {
                    for(int j=0;j<=cnow;++j)
                        for(int k=0;k<=childs[id[i+1]];++k)
                            if(j+k<=m)
                                Update(dp2[i+1][j+k],dp2[i][j]+maxv[i+1][k]);
                    cnow+=childs[id[i+1]];
                }
                for(int i=0;i<=m;++i)
                    dp[u][i][belong]=dp2[tot][i];
            }
            else
            {
                for(int i=0;i<=tot;++i)
                    for(int j=0;j<=m;++j)
                        dp2[i][j]=-inf;
                dp2[0][1]=0;
                int cnow=1;
                for(int i=0;i<tot;++i)
                {
                    for(int j=0;j<=cnow;++j)
                        for(int k=0;k<=childs[id[i+1]];++k)
                            if(j+k<=m)
                                Update(dp2[i+1][j+k],dp2[i][j]+max(maxv[i+1][k],dp[id[i+1]][k+1][belong]));
                    cnow+=childs[id[i+1]];
                }
                for(int i=0;i<=m;++i)
                    dp[u][i][belong]=dp2[tot][i]+1;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v);
            g[u][v]=g[v][u]=w;
        }
        for(int i=1;i<=n;++i)
            scanf("%d",&flag[i]);
        floyd();
        getpremart();
        dfs(1,-1);
        int ans=-inf;
        for(int i=0;i<=m;++i)
            for(int j=1;j<=n;++j)
                ans=max(ans,dp[1][i][j]);
        printf("%d\n",ans);
    }
    return 0;
}
