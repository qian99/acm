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
const int maxn=100000+10;
const int maxm=300000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],dp[maxn],w[maxn],nEdge;
int pre[maxn],sccno[maxn],dfs_clock,scc_cnt;
stack<int>S;
vector<int>g[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowu,lowv);
        }
        else if(!sccno[v])
            lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        scc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void dfs(int u)
{
    if(dp[u]!=-1) return ;
    dp[u]=w[u];
    for(int i=0;i<(int)g[u].size();++i)
    {
        int v=g[u][i];
        dfs(v);
        dp[u]=max(dp[u],dp[v]+w[u]);
    }
}
int solve(int n)
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(w,0,sizeof(w));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
        if(!pre[i]) tarjan(i);
    for(int i=0;i<=n;++i) g[i].clear();
    for(int i=1;i<=n;++i)
    {
        w[sccno[i]]++;
        for(int k=head[i];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(sccno[i]!=sccno[v])
                g[sccno[i]].push_back(sccno[v]);
        }
    }
    memset(dp,0xff,sizeof(dp));
    int ans=0;
    for(int i=1;i<=scc_cnt;++i)
    {
        if(dp[i]==-1)
            dfs(i);
        ans=max(ans,dp[i]);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        int ans=solve(n);
        printf("%d\n",ans);
    }
    return 0;
}