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
const int maxn = 55;
const int maxm = 2500 + 10;
char mat[maxn][maxn];
int row[maxn][maxn],col[maxn][maxn];
vector<int>G[maxm];
int links[maxm],vis[maxm],T;
int dfs(int u)
{
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        if(vis[v] != T)
        {
            vis[v] = T;
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
    memset(links,0xff,sizeof(links));
    int res = 0;
    for(int i = 1;i <= n;++i)
    {
        T++;
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(vis,0,sizeof(vis));
    T = 0;
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n;++i)
            scanf("%s",mat[i]);
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        int rid = 0,cid = 0,ans = 0;
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j < m;++j)
            {
//                if(mat[i][j] == '*') ans++;
                if(mat[i][j] != '*' || row[i][j]) continue;
                int dy = j;
                rid++;
                while(dy < m && mat[i][dy] != '#')
                    row[i][dy++] = rid;
            }
        }
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j < m;++j)
            {
                if(mat[i][j] != '*' || col[i][j]) continue;
                int dx = i;
                cid++;
                while(dx < n && mat[dx][j] != '#')
                    col[dx++][j] = cid;
            }
        }
        int N = rid;
        for(int i = 0;i <= N;++i) G[i].clear();
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j)
                if(mat[i][j] == '*' && row[i][j] && col[i][j])
                    G[row[i][j]].push_back(col[i][j]);
        ans = hungary(N);
        printf("%d\n",ans);
    }
    return 0;
}
