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
const int maxn=50000+10;
int pre[maxn],sccno[maxn],costs[maxn],dfs_clock,scc_cnt;
vector<int>G[maxn];
stack<int>S;
struct Edge
{
    int u,v,w;
};
vector<Edge>edges;
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowv,lowu);
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
void slove(int n)
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=0;i<n;++i)
       if(!pre[i]) tarjan(i);
    for(int i=1;i<=scc_cnt;++i) costs[i]=inf;
    for(int i=0;i<edges.size();++i)
    {
        Edge e=edges[i];
        if(sccno[e.u]!=sccno[e.v])
          costs[sccno[e.v]]=min(costs[sccno[e.v]],e.w);
    }
    int sum=0;
    for(int i=1;i<=scc_cnt;++i)
        if(costs[i]!=inf) sum+=costs[i];
    printf("%d\n",sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int a,b,c;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            edges.push_back((Edge){a,b,c});
            G[a].push_back(b);
        }
        slove(n);
    }
    return 0;
}
