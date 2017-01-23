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
const int maxn=2000+10;
int g[maxn][maxn],pre[maxn],sccno[maxn],dfs_clock,scc_cnt,n;
stack<int>S;
int dfs(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int v=1;v<=n;++v)
    {
        if(!g[u][v]) continue;
        if(!pre[v])
        {
            int lowv=dfs(v);
            lowu=min(lowu,lowv);
        }
        else if(!sccno[v])
            lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        scc_cnt++;
        while(!S.empty())
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
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
        if(!pre[i]) dfs(i);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&g[i][j]);
    find_scc();
    if(scc_cnt==1)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}