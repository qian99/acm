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
const int maxn=1000000+10;
int degree[maxn],dp[maxn];
bool vis[maxn];
vector<int>g[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,u,v,s,t;
    scanf("%d%d",&n,&m);
    memset(degree,0,sizeof(degree));
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        g[v].push_back(u);
        degree[u]++;
    }
    scanf("%d%d",&s,&t);
    deque<int>q;
    q.push_front(t);
    dp[t]=0;
    while(!q.empty())
    {
        u=q.front();q.pop_front();
        if(u==s) break;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<(int)g[u].size();++i)
        {
            v=g[u][i];
            degree[v]--;
            if(degree[v]==0)
            {
                if(dp[v]>dp[u])
                {
                    dp[v]=dp[u];
                    q.push_front(v);
                }
            }
            else
            {
                if(dp[v]>dp[u]+1)
                {
                    dp[v]=dp[u]+1;
                    q.push_back(v);
                }
            }
        }
    }
    int ans=dp[s]==inf?-1:dp[s];
    printf("%d\n",ans);
    return 0;
}
