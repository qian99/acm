#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
vector<int>G[maxn];
int dp[maxn][2];
bool vis[maxn];
void dfs(int u,int fa)
{
    vis[u]=true;
    dp[u][0]=0;dp[u][1]=2000+1;
    if(fa<0) dp[u][1]--;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v!=fa)
        {
            dfs(v,u);
            dp[u][0]+=dp[v][1];
            if(dp[v][0]+1<dp[v][1]-1) dp[u][1]+=(dp[v][0]+1);
            else dp[u][1]+=(dp[v][1]-1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) G[i].clear();
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        memset(vis,0,sizeof(vis));
        int ans=0;
        for(int i=0;i<n;++i)
        {
            if(!vis[i])
            {
                dfs(i,-1);
                ans+=min(dp[i][0],dp[i][1]);
            }
        }
        printf("%d %d %d\n",ans/2000,m-ans%2000,ans%2000);
    }
    return 0;
}
