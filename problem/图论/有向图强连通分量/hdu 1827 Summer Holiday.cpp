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
int pre[maxn],sccno[maxn],ind[maxn],value[maxn],costs[maxn],dfs_clock,scc_cnt;
vector<int>G[maxn];
stack<int>S;
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
    memset(ind,0,sizeof(ind));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
       if(!pre[i]) tarjan(i);
    for(int i=1;i<=scc_cnt;++i) costs[i]=inf;
    for(int i=1;i<=n;++i)
       costs[sccno[i]]=min(costs[sccno[i]],value[i]);
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(sccno[u]!=sccno[v])
                ind[sccno[v]]++;
        }
    }
    int sum=0,num=0;
    for(int i=1;i<=scc_cnt;++i)
        if(!ind[i]) sum+=costs[i],num++;
    printf("%d %d\n",num,sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int a,b;
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=1;i<=n;++i)
           scanf("%d",&value[i]);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
        }
        slove(n);
    }
    return 0;
}
