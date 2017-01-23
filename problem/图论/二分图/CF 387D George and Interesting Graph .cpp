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
const int maxn=500+10;
vector<int>G[maxn];
int links[maxn],a[maxn][maxn],ind[maxn],outd[maxn],n,m,ans;
bool vis[maxn];
bool dfs(int u,int cen)
{
    for(int i=0;i<(int)G[u].size();++i)
    {
        int v=G[u][i];
        if(v==cen) continue;
        if(!vis[v])
        {
            vis[v]=true;
            if(links[v]==-1||dfs(links[v],cen))
            {
                links[v]=u;
                return true;
            }
        }
    }
    return false;
}
void cal(int x)
{
    int sum=(n-1)*2+1-(ind[x]+outd[x]);
    if(a[x][x]) sum++;
    memset(links,0xff,sizeof(links));
    int cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(i==x) continue;
        memset(vis,0,sizeof(vis));
        if(dfs(i,x)) cnt++;
    }
    for(int i=1;i<=n;++i)
    {
        if(i==x) continue;
        sum+=outd[i];
        if(a[i][x]) sum--;
    }
    sum-=cnt;
    sum+=(n-1-cnt);
    ans=min(sum,ans);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        a[u][v]=1;
        ind[v]++;outd[u]++;
    }
    ans=inf;
    for(int i=1;i<=n;++i)
        cal(i);
    printf("%d\n",ans);
    return 0;
}

