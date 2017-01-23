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
const int maxn=1000+10;
const int mod=10086;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],dp[maxn][maxn],son[maxn],dp2[maxn][3],nEdge;
int res[2],d[maxn],S[maxn],p[maxn],minlen;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u][0]=dp[u][1]=0;
    son[u]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        if(dp[v][0]+1>dp[u][0])
        {
            dp[u][1]=dp[u][0];
            dp[u][0]=dp[v][0]+1;
            son[u]=v;
        }
        else if(dp[v][0]+1>dp[u][1])
            dp[u][1]=dp[v][0]+1;
    }
}
void dfs2(int u,int fa,int maxlen)
{
    int tmp=max(maxlen,dp[u][0]);
    if(tmp<minlen)
    {
        minlen=tmp;
        res[0]=u;
        res[1]=-1;
    }
    else if(tmp==minlen)
        res[1]=u;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        tmp=(son[u]==v)?dp[u][1]+1:dp[u][0]+1;
        dfs2(v,u,max(maxlen+1,tmp));
    }
}
void init()
{
    memset(head,0xff,sizeof(head));
    memset(son,0,sizeof(son));
    memset(d,0,sizeof(d));
    nEdge=res[0]=res[1]=-1;
    minlen=inf;
}
void DFS(int u,int fa)
{
    for(int i=0;i<maxn;++i) dp[u][i]=1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        DFS(v,u);
        for(int i=1;i<maxn;++i)
            dp[u][i]=(dp[u][i]+dp[u][i]*dp[v][i-1])%mod;
    }
}
int solve(int n)
{
    dfs(1,-1);
    dfs2(1,-1,0);
    int type=(res[1]!=-1);
    DFS(res[0],res[1]);
    if(type) DFS(res[1],res[0]);
    int ans=1,size;
    if(type==0)
    {
        size=0;
        for(int k=head[res[0]];k!=-1;k=edges[k].next)
            S[++size]=edges[k].v;
        if(size>1) ans=(ans+p[size]-size-1)%mod;
        for(int i=1;i<maxn;++i)
        {
            dp2[0][0]=1;dp2[0][1]=dp2[0][2]=0;
            for(int j=1;j<=size;++j)
            {
                dp2[j][0]=dp2[j-1][0]*(1+dp[S[j]][i-1])%mod;
                dp2[j][1]=dp2[j-1][1]*(1+dp[S[j]][i-1])%mod+dp2[j-1][0]*(dp[S[j]][i]-dp[S[j]][i-1])%mod;
                dp2[j][2]=dp2[j-1][2]*(1+dp[S[j]][i-1])%mod+(dp2[j-1][1]+dp2[j-1][2])*(dp[S[j]][i]-dp[S[j]][i-1])%mod;
                dp2[j][1]%=mod;dp2[j][2]%=mod;
            }
            ans=(ans+dp2[size][2])%mod;
        }
    }
    else
    {
        int tmp1,tmp2;
        for(int i=1;i<maxn;++i)
        {
            tmp1=dp[res[0]][i]-dp[res[0]][i-1];
            tmp2=dp[res[1]][i]-dp[res[1]][i-1];
            ans=(ans+tmp1*tmp2)%mod;
        }
    }
    return (ans%mod+mod)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=(p[i-1]<<1)%mod;
    int n,t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        init();
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        printf("Case %d: %d\n",++tcase,solve(n));
    }
    return 0;
}
