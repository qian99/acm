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
const int mod=10007;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge,n;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
///find centriod
int wval,wroot[2],childs[maxn];
void fcen(int u,int fa)
{
    childs[u]=1;
    int wmax=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        fcen(v,u);
        childs[u]+=childs[v];
        wmax=max(childs[v],wmax);
    }
    wmax=max(wmax,n-childs[u]);
    if(wmax<wval)
    {
        wval=wmax;
        wroot[0]=u;wroot[1]=-1;
    }
    else if(wmax==wval)
        wroot[1]=u;
}
///cal w[i][j]
int w[maxn][maxn];
void dfs(int u,int fa)
{
    w[u][0]=w[u][1]=1;
    childs[u]=1;
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
        for(int i=childs[u];i>=2;--i)
        {
            for(int j=1;j<i&&j<=childs[v];++j)
            {
                w[u][i]+=w[v][j]*w[u][i-j];
                if(w[u][i]>=mod) w[u][i]%=mod;
            }
        }
    }
}
///solve1
int dp[maxn];
int solve1()
{
    dfs(wroot[0],-1);
    int rt=wroot[0];
    int ans=0;
    for(int i=1;i<=n;++i)
        ans=(ans+w[rt][i])%mod;
    for(int k=head[rt];k!=-1;k=edges[k].next)
    {
        for(int i=0;i<=n;++i) dp[i]=w[rt][i];
        int v=edges[k].v;
        for(int i=1;i<=n;++i)
            for(int j=1;j<i;++j)
            {
                dp[i]-=dp[i-j]*w[v][j];
                if(dp[i]<0) dp[i]=(dp[i]%mod+mod)%mod;
            }
        dp[0]=1;
        for(int i=1;i<n;++i)
            dp[i]=(dp[i-1]+dp[i+1])%mod;
        for(int i=1;i<=n;++i)
        {
            ans-=w[v][i]*dp[i-1];
            ans=(ans%mod+mod)%mod;
        }
    }
    return ans;
}
///solve2
int solve2()
{
    dfs(wroot[0],wroot[1]);
    dfs(wroot[1],wroot[0]);
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        ans+=w[wroot[0]][i]*w[wroot[1]][i];
        ans%=mod;
    }
    return ans;
}

void Init()
{
    memset(head,0xff,sizeof(head));
    memset(w,0,sizeof(w));
    nEdge=-1;
    wroot[0]=wroot[1]=-1;
    wval=inf;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        Init();
        int u,v,ans;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        fcen(1,-1);
        if(wroot[1]==-1) ans=solve1();
        else ans=solve2();
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}
