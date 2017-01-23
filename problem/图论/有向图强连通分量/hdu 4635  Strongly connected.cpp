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
typedef long long LL;
const int maxn=100000+10;
struct Edge
{
    int u,v;
};
vector<int>G[maxn];
int pre[maxn],low[maxn],sccno[maxn],dfs_clock,scc_cnt;
int ind[maxn],outd[maxn],pointnum[maxn];
stack<int>S;
int n,m;
void dfs(int u)
{
    pre[u]=low[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!sccno[v])
            low[u]=min(low[u],pre[v]);
    }
    if(low[u]==pre[u])
    {
        scc_cnt++;
        for(;;)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
void find_scc()
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
       if(!pre[i]) dfs(i);
}
int slove()
{
    if(scc_cnt==1) return -1;
    memset(ind,0,sizeof(ind));
    memset(outd,0,sizeof(outd));
    memset(pointnum,0,sizeof(pointnum));
    for(int i=1;i<=n;++i)
       pointnum[sccno[i]]++;
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
    int minval=inf;
    for(int i=1;i<=scc_cnt;++i)
    {
        if(ind[i]==0&&pointnum[i]<minval)
            minval=pointnum[i];
        if(outd[i]==0&&pointnum[i]<minval)
            minval=pointnum[i];
    }
    int ans=n*n-n-minval*(n-minval);
    return ans-m;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) G[i].clear();
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
        }
        find_scc();
        int ans=slove();
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}
