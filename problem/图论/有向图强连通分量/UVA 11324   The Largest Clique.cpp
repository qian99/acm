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
const int maxn=1000+10;
int pre[maxn],lowlink[maxn],sccno[maxn],value[maxn],maxv[maxn],dfs_clock,scc_cnt;
vector<int>G[maxn];
vector<int>g[maxn];
stack<int>S;
void dfs(int u)
{
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])
        {
            lowlink[u]=min(lowlink[u],pre[v]);
        }
    }
    if(lowlink[u]==pre[u])
    {
        scc_cnt++;
        for(;;)
        {
            int x=S.top();
            S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
void find_scc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(lowlink,0,sizeof(lowlink));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(!pre[i]) dfs(i);
    }
}
int dfsdag(int u)
{
    if(g[u].size()==0) return maxv[u]=value[u];
    if(maxv[u]) return maxv[u];
    int maxvalue=0;
    for(int i=0;i<g[u].size();++i)
    {
        int v=g[u][i];
        maxvalue=max(maxvalue,dfsdag(v));
    }
    return maxv[u]=maxvalue+value[u];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        int a,b;
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            if(a==b) continue;
            G[a].push_back(b);
        }
        find_scc(n);
        memset(value,0,sizeof(value));
        memset(maxv,0,sizeof(maxv));
        for(int i=1;i<=scc_cnt;++i)
            g[i].clear();
        for(int i=1;i<=n;++i)
            value[sccno[i]]++;
        for(a=1;a<=n;++a)
        {
            for(int j=0;j<G[a].size();++j)
            {
                b=G[a][j];
                if(sccno[a]!=sccno[b])
                  g[sccno[a]].push_back(sccno[b]);
            }
        }
        int ans=0;
        for(int i=1;i<=scc_cnt;++i)
        {
            ans=max(ans,dfsdag(i));
        }
        printf("%d\n",ans);
    }
    return 0;
}
