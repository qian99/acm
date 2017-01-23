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
const int maxn=35;
int g[maxn][maxn],deadline[maxn],n,ans;
bool vis[maxn];
void dfs(int u,int w,int sum,int cnt)
{
    if(cnt==n)
    {
        ans=min(ans,sum);
        return ;
    }
    if(sum>=ans) return ;
    for(int i=2;i<=n;++i)
        if(!vis[i])
        {
            if(w+g[u][i]>deadline[i]) return ;
        }
    for(int i=2;i<=n;++i)
        if(!vis[i])
        {
            if((w+g[u][i])*(n-cnt-1)+sum>ans) continue;
            vis[i]=true;
            dfs(i,w+g[u][i],sum+w+g[u][i],cnt+1);
            vis[i]=false;
        }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&g[i][j]);
        for(int k=1;k<=n;++k)
            for(int i=1;i<=n;++i)
                for(int j=1;j<=n;++j)
                    g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
        deadline[1]=inf;
        for(int i=2;i<=n;++i)
            scanf("%d",&deadline[i]);
        memset(vis,0,sizeof(vis));
        vis[1]=true;
        ans=inf;
        dfs(1,0,0,1);
        if(ans==inf) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
