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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500+10;
int g[maxn][maxn],ans[maxn],degree[maxn];
bool vis[maxn];
char mat[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        for(int i = 1; i <= n;++i)
        {
            scanf("%s",mat[i]+1);
            for(int j = 1;j <= n;++j)
                g[i][j] = mat[i][j] - '0';
        }
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(g[i][j]) degree[j]++;
        for(int i = 1;i <= n;++i)
        {
            int u = -1;
            for(int j = 1;j <= n;++j)
            {
                if(!vis[j])
                {
                    if(u == -1) u = j;
                    else if(degree[u] < degree[j])
                        u = j;
                }
            }
            ans[i] = u;
            vis[u] = true;
            for(int j = 1;j <= n;++j)
                if(g[u][j]) degree[j]--;
        }
        reverse(ans+1,ans + n +1);
        for(int i = 1;i <= n;++i)
        {
            if(i > 1) printf(" ");
            printf("%d",ans[i]);
        }
        printf("\n");
    }
    return 0;
}
