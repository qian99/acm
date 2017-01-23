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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
vector<int>G[maxn];
int link[maxn],a[maxn],b[maxn];
bool vis[maxn];
bool dfs(int u)
{
    for(int i=0;i<(int)G[u].size();++i)
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
int solve(int n)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int L,R;
    int n;
    while(~scanf("%d%d",&R,&L))
    {
        scanf("%d",&n);
        int x,y;
        int nn=0,mm=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            if(y) b[++mm]=x;
            else a[++nn]=x;
        }
        for(int i=1;i<=nn;++i) G[i].clear();
        for(int i=1;i<=nn;++i)
          for(int j=1;j<=nn;++j)
            if(b[j]>a[i]&&((b[j]-a[i])<=L||(b[j]-a[i])>=R))
            {
                G[i].push_back(j);
                //G[j].push_back(i);
            }
        int ans=solve(nn);
        if(ans==n/2)
        {
            printf("No reason\n");
            for(int i=1;i<=mm;++i)
            {
                printf("%d %d\n",a[link[i]],b[i]);
            }
        }
        else printf("Liar\n");
    }
    return 0;
}
