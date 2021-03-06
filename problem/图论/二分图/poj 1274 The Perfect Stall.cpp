#include<iostream>
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
typedef long long ll;
const int maxn=200+10;
int g[maxn][maxn],links[maxn],n,m;
bool vis[maxn];
bool dfs(int u)
{
    for(int i=1;i<=m;++i)
    {
        if(!vis[i]&&g[u][i])
        {
            vis[i]=true;
            if(links[i]==-1||dfs(links[i]))
            {
                links[i]=u;
                return true;
            }
        }
    }
    return false;
}
int Hungary()
{
    memset(links,0xff,sizeof(links));
    int cnt=0;
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k;
    while(~scanf("%d%d",&n,&m))
    {
        memset(g,0,sizeof(g));
        int v;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&v);
                g[i][v]=1;
            }
        }
        int ans=Hungary();
        printf("%d\n",ans);
    }
    return 0;
}
