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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
int g[maxn][maxn],links[maxn],n;
int a[maxn],vis[maxn],cnt;
bool dfs(int u)
{
    for(int i = 1;i <= n;++i)
    {
        if(g[u][i] && vis[i] != cnt)
        {
            vis[i] = cnt;
            if(links[i] == -1 || dfs(links[i]))
            {
                links[i] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int res = 0;
    memset(links,0xff,sizeof(links));
    for(int i = 1;i <= n;++i)
    {
        cnt++;
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cnt = 0;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int k;
        scanf("%d%d",&n,&k);
        memset(g,0,sizeof(g));
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        for(int i = 1;i <= n;++i)
        {
            for(int j = 0;a[i] + j*k <= n;++j)
                g[i][a[i] + j*k] = 1;
        }
        int res = hungary();
        if(res == n)
            puts("Jerry");
        else
            puts("Tom");
    }
    return 0;
}
