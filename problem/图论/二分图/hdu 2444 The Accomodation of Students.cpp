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
const int maxn=200+10;
vector<int>G[maxn];
int link[maxn],color[maxn];
bool vis[maxn];
bool isbipartite(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(color[u]==color[v]) return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!isbipartite(v)) return false;
        }
    }
    return true;
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!vis[v])
        {
            vis[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) res++;
    }
    return res/2;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==1)
        {
            printf("No\n");
            continue;
        }
        for(int i=0;i<=n;++i) G[i].clear();
        memset(color,0,sizeof(color));
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        bool flag=true;
        for(int i=1;i<=n;++i)
        {
            if(!color[i])
            {
                color[i]=1;
                if(!isbipartite(i)) flag=false;
            }
        }
        if(!flag)
          printf("No\n");
        else
          printf("%d\n",hungary(n));
    }
    return 0;
}
