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
vector<int>G[maxn];
int pre[maxn],ebcno[maxn],degree[maxn],dfs_clock,ebc_cnt;
stack<int>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            lowu=min(lowu,pre[v]);
        }
    }
    if(lowu==pre[u])
    {
        ebc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            ebcno[x]=ebc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_ebc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(ebcno,0,sizeof(ebcno));
    while(!S.empty()) S.pop();
    dfs_clock=ebc_cnt=0;
    for(int i=1;i<=n;++i)
      if(!pre[i]) dfs(i,-1);
}
int slove(int n)
{
    if(ebc_cnt==1) return 0;
    memset(degree,0,sizeof(degree));
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(ebcno[u]!=ebcno[v])
            {
                degree[ebcno[u]]++;
                degree[ebcno[u]]++;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=ebc_cnt;++i)
    {
        if(degree[i]==0) ans+=2;
        if(degree[i]==2) ans++;
    }
    return (ans+1)/2;
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
            G[b].push_back(a);
        }
        find_ebc(n);
        int ans=slove(n);
        printf("%d\n",ans);
    }
    return 0;
}
