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
const int maxm=50000+10;
int pre[maxn],lowlink[maxn],sccno[maxn],ind[maxn],outd[maxn],dfs_clock,scc_cnt;
stack<int>S;
vector<int>G[maxn];
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
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
void find_scc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(!pre[i]) dfs(i);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int a,b;
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
        }
        find_scc(n);
        for(int i=1;i<=scc_cnt;++i)
           ind[i]=outd[i]=0;
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
        a=b=0;
        for(int i=1;i<=scc_cnt;++i)
        {
            if(ind[i]==0) a++;
            if(outd[i]==0) b++;
        }
        int ans=max(a,b);
        if(scc_cnt==1) ans=0;
        printf("%d\n",ans);
    }
    return 0;
}
