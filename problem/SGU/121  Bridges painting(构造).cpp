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
const int maxn=100+10;
vector<int>G[maxn];
int color[maxn][maxn],degree[maxn],n;
void dfs(int u,int c)
{
    c=3-c;
    int sz=G[u].size();
    for(int i=0;i<sz;++i)
    {
        int v=G[u][i];
        if(!color[u][v])
        {
            color[u][v]=color[v][u]=c;
            dfs(v,c);
            c=3-c;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    memset(color,0,sizeof(color));
    memset(degree,0,sizeof(degree));
    for(int i=0;i<=n;++i) G[i].clear();
    int u,v;
    for(u=1;u<=n;++u)
    {
        while(~scanf("%d",&v))
        {
            if(v==0) break;
            G[u].push_back(v);
            degree[u]++;
        }
    }
    for(u=1;u<=n;++u)
      if(degree[u]&1) dfs(u,1);
    for(u=1;u<=n;++u)
      dfs(u,1);
    bool flag=true;
    for(u=1;u<=n;++u)
    {
        if(degree[u]>1)
        {
            int sz=G[u].size();
            int k=0;
            for(int j=0;j<sz;++j)
            {
                v=G[u][j];
                k|=color[u][v];
            }
            if(k!=3)
            {
                flag=false;
                break;
            }
        }
    }
    if(!flag)
    {
        printf("No solution\n");
    }
    else
    {
        for(u=1;u<=n;++u)
        {
            int sz=G[u].size();
            for(int j=0;j<sz;++j)
            {
                v=G[u][j];
                printf("%d ",color[u][v]);
            }
            printf("0\n");
        }
    }
    return 0;
}
