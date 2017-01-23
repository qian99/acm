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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
ll dp[maxn][1110];
int x[maxn],w[maxn],t[maxn];
int g[maxn][maxn];
int dis[maxn];
bool vis[maxn];
void dijkstra(int n)
{
    memset(vis,false,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=n;++i)
        dis[i]=g[0][i];
    vis[0]=true;
    int mind=0;
    int pos;
    for(int i=0;i<n;++i)
    {
        mind=inf;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j]&&mind>dis[j])
            {
                mind=dis[j];
                pos=j;
            }
        }
        vis[pos]=true;
        for(int k=1;k<=n;++k)
        {
            if(!vis[k]&&mind+g[pos][k]<dis[k])
            {
                dis[k]=mind+g[pos][k];
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,T;
    while(~scanf("%d%d%d",&n,&m,&T))
    {
        memset(dp,0,sizeof(dp));
        memset(g,0x3f,sizeof(g));
        for(int i=1;i<=n;++i)
            scanf("%d%d%d",&x[i],&w[i],&t[i]);
        int u,v,cost;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&cost);
            if(g[u][v]>cost) g[u][v]=cost;
        }
        for(int i=0;i<=n;++i) g[i][i]=0;
        dijkstra(n);
        for(int i=1;i<=n;++i)
        {
            int times=dis[i];
            for(int j=0;j<=T;++j)
            {
                if(times+j>T) break;
                for(int k=1;k<=x[i];++k)
                    if(times+j+k*t[i]<=T)
                        dp[i][times+j+k*t[i]]=max(dp[i][times+j+k*t[i]],dp[i-1][j]+k*w[i]);
            }
            for(int j=0;j<=T;++j)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        ll ans=0;
        for(int i=0;i<=T;++i)
            ans=max(ans,dp[n][i]);
        printf("%lld\n",ans);
    }
    return 0;
}