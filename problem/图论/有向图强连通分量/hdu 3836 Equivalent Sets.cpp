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
const int maxn=20000+10;
int pre[maxn],sccno[maxn],ind[maxn],outd[maxn],dfs_clock,scc_cnt;
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
int slove(int n)
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(ind,0,sizeof(ind));
    memset(outd,0,sizeof(outd));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
       if(!pre[i]) tarjan(i);
    if(scc_cnt==1) return 0;
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(sccno[u]!=sccno[v])
            {
                ind[sccno[v]]++;
                outd[sccno[u]]++;
            }
        }
    }
    int a=0,b=0;
    for(int i=1;i<=scc_cnt;++i)
    {
        if(!ind[i]) a++;
        if(!outd[i]) b++;
    }
    return max(a,b);
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
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
        }
        printf("%d\n",slove(n));
    }
    return 0;
}
