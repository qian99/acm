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
stack<int>S;
int pre[maxn],id[maxn],dfs_clock,ecc_cnt;
int degree[maxn];
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
        ecc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            id[x]=ecc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_ecc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(id,0,sizeof(id));
    while(!S.empty()) S.pop();
    dfs_clock=ecc_cnt=0;
    for(int i=1;i<=n;++i)
      if(!pre[i]) dfs(i,-1);
}
int slove(int n)
{
    int sum=0;
    memset(degree,0,sizeof(degree));
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(id[u]!=id[v])
            {
                degree[id[u]]++;
                degree[id[v]]++;
            }
        }
    }
    for(int i=1;i<=ecc_cnt;++i)
       if(degree[i]==2) sum++;
    return (sum+1)/2;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        //if(n==0&&m==0) break;
        int a,b;
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        find_ecc(n);
        int ans=slove(n);
        printf("%d\n",ans);
    }
    return 0;
}
