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
const int maxn = 3000 + 10;
vector<int>G[maxn];
int links[maxn],vis[maxn],cnt;
char mat[55][55];
int rowid[55][55],colid[55][55];
bool dfs(int u)
{
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        if(vis[v] != cnt)
        {
            vis[v] = cnt;
            if(links[v] == -1 || dfs(links[v]))
            {
                links[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    memset(vis,0,sizeof(vis));
    memset(links,0xff,sizeof(links));
    cnt = 0;
    int res = 0;
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
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        for(int i = 0;i < m;++i)
            scanf("%s",mat[i]);
        int M = 0,N = 0;
        for(int i = 0;i < m;++i)
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == '#') continue;
                int k = j;
                ++M;
                while(k < n && mat[i][k] != '#') rowid[i][k++] = M;
                j = k;
            }
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j)
            {
                if(mat[j][i] == '#') continue;
                int k = j;
                ++N;
                while(k < m && mat[k][i] != '#') colid[k++][i] = N;
                j = k;
            }
        for(int i = 1;i <= M;++i)
            G[i].clear();
        for(int i = 0;i < m;++i)
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == 'o')
                {
                    G[rowid[i][j]].push_back(colid[i][j]);
                }
            }
        printf("Case :%d\n",++tcase);
        printf("%d\n",hungary(M));
    }
    return 0;
}
