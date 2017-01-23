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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
using namespace std;
const int maxn=30000+10;
const int maxm=150000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxm],ee[maxm];
int pre[maxn],head[maxn],hh[maxn],nEdge,ecnt;
int sccno[maxn],scc_cnt,dfs_clock,n,m;
int w[maxn],val[maxn],dp[maxn];
stack<int>S;
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(hh,0xff,sizeof(hh));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(dp,0xff,sizeof(dp));
    memset(val,0,sizeof(val));
    nEdge=ecnt=-1;
    scc_cnt=dfs_clock=0;
}
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void addedge(int u,int v)
{
    ecnt++;
    ee[ecnt].v=v;
    ee[ecnt].next=hh[u];
    hh[u]=ecnt;
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
int dfs(int u)
{
    if(dp[u]>=0) return dp[u];
    dp[u]=val[u];
    int tmp=0;
    for(int k=hh[u];k!=-1;k=ee[k].next)
    {
        int v=ee[k].v;
        dfs(v);
        tmp=max(tmp,dp[v]);
    }
    return dp[u]+=tmp;
}
int solve()
{
    for(int i=1;i<=n;++i)
      if(!pre[i]) tarjan(i);
    int u,v;
    for(u=1;u<=n;++u)
    {
        val[sccno[u]]+=w[u];
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(sccno[u]!=sccno[v])
              addedge(sccno[u],sccno[v]);
        }
    }
    int ans=0;
    for(int i=1;i<=scc_cnt;++i)
    {
        if(dp[i]==-1) dfs(i);
        ans=max(ans,dp[i]);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w[i]);
            if(w[i]<0) w[i]=0;
        }
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            u++;v++;
            AddEdge(u,v);
        }
        int res=solve();
        printf("%d\n",res);
    }
    return 0;
}
