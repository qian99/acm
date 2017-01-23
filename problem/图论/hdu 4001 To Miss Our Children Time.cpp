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
const int maxn=1000+10;
struct Node
{
    int a,b,d;
};
struct Edge
{
    int v;
    int next;
};
Node node[maxn];
int head[maxn],hd[maxn],w[maxn];
ll val[maxn],dp[maxn],ans;
Edge edges[maxn*maxn],ee[maxn*maxn];
int pre[maxn],sccno[maxn],dfs_clock,scc_cnt,nEdge,nedge,n;
stack<int>S;
void AddEdges(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void addedges(int u,int v)
{
    nedge++;
    ee[nedge].v=v;
    ee[nedge].next=hd[u];
    hd[u]=nedge;
}
bool check(int i,int j)
{
    if(node[i].d==0)
      return node[i].a>=node[j].a&&node[i].b>=node[j].b;
    if(node[i].d==1)
      return node[i].a>=node[j].a&&node[i].b>=node[j].b&&(node[i].a>node[j].a||node[i].b>node[j].b);
    return node[i].a>node[j].a&&node[i].b>node[j].b;
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
        for(;;)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_scc()
{
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
      if(!pre[i]) tarjan(i);
}
ll dfs(int u)
{
    if(dp[u]!=-1) return dp[u];
    dp[u]=val[u];
    for(int k=hd[u];k!=-1;k=ee[k].next)
    {
        int v=ee[k].v;
        dp[u]=max(dp[u],dfs(v)+val[u]);
    }
    return dp[u];
}
void solve()
{
    ans=0;
    memset(val,0,sizeof(val));
    memset(dp,0xff,sizeof(dp));
    memset(hd,0xff,sizeof(hd));
    nedge=-1;
    for(int i=1;i<=n;++i)
    {
        val[sccno[i]]+=w[i];
        for(int k=head[i];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(sccno[i]!=sccno[v])
              addedges(sccno[i],sccno[v]);
        }
    }
    for(int i=1;i<=scc_cnt;++i)
       ans=max(ans,dfs(i));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int c;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d%d",&node[i].a,&node[i].b,&w[i],&node[i].d);
            if(node[i].a<node[i].b)
            {
                c=node[i].a;
                node[i].a=node[i].b;
                node[i].b=c;
            }
        }
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        bool flag;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(i==j) continue;
                if(check(i,j))
                   AddEdges(i,j);
            }
        }
        find_scc();
        solve();
        printf("%I64d\n",ans);
    }
    return 0;
}
