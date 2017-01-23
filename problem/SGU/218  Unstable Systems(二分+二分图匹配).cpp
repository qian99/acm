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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
int g[maxn][maxn],links[maxn],n,lim;
bool vis[maxn];
bool dfs(int u)
{
    for(int i=1;i<=n;++i)
    {
        if(!vis[i]&&g[u][i]<=lim)
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
int hungary(int mid)
{
    lim=mid;
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&g[i][j]);
    int l=-1000000,r=1000000;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(hungary(mid)==n) r=mid;
        else l=mid+1;
    }
    hungary(l);
    printf("%d\n",l);
    for(int i=1;i<=n;++i)
        printf("%d %d\n",links[i],i);
    return 0;
}
