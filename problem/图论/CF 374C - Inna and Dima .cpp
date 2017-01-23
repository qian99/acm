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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
const int dirx[4] = {1,-1,0,0};
const int diry[4] = {0,0,1,-1};
char mat[maxn][maxn];
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn*maxn*4];
int head[maxn*maxn],nEdge;
int dp[maxn*maxn],n,m;
int vis[maxn*maxn],flag;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
inline char nextChar(char c)
{
    if(c == 'D') return 'I';
    if(c == 'I') return 'M';
    if(c == 'M') return 'A';
    return 'D';
}
inline bool check(int x,int y)
{
    return x >= 0 && x < n && y >=0 && y<m;
}
int dfs(int u)
{
    if(dp[u] == -2) return -1;
    if(dp[u] != -1) return dp[u];
    dp[u] = -2;
    int res = 1;
    for(int k = head[u];k!=-1;k=edges[k].next)
    {
        int v = edges[k].v;
        if(dfs(v) == -1) return -1;
        res = max(res,dp[v] + 1);
    }
    return dp[u] = res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++i)
        scanf("%s",mat[i]);
    memset(head,0xff,sizeof(head));
    memset(dp,0xff,sizeof(dp));
    memset(vis,0,sizeof(vis));
    nEdge = -1;
    int x , y;
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < m;++j)
        {
            for(int k = 0;k < 4;++k)
            {
                x = i + dirx[k];
                y = j + diry[k];
                if(check(x,y) && nextChar(mat[i][j]) == mat[x][y])
                    AddEdges(i*m+j,x*m+y);
            }
        }
    }
    flag = 0;
    int ans = 0;
    for(int i = 0;i < n*m;++i)
    {
        if(dfs(i) == -1)
        {
            flag = 1;
            break;
        }
        if(mat[i/m][i%m] == 'D')
            ans = max(ans,dp[i]);
    }
    if(flag) puts("Poor Inna!");
    else if(ans <4) puts("Poor Dima!");
    else printf("%d\n",ans/4);
    return 0;
}
