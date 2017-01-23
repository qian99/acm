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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 2000+10;
const int dirx[4] = {0,1,0,-1};
const int diry[4] = {1,0,-1,0};
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn*maxn];
int head[maxn*maxn],nEdge;
int vis[maxn*maxn],dp[maxn*maxn],vec[maxn][maxn];
char a[maxn][maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
bool DFS(int u,int id)
{
    vis[u] = id;
    for(int k = head[u];k != -1;k=edges[k].next)
    {
        int v =edges[k].v;
        if(vis[v] == id) return false;
        if(vis[v] && vis[v] != id) continue;
        if(!DFS(v,id)) return false;
    }
    return true;
}
inline int getDir(char c)
{
    if(c == '<') return 2;
    if(c == '>') return 0;
    if(c == '^') return 3;
    return 1;
}
void dfs(int u)
{
    dp[u] = 0;
    for(int k = head[u];k!=-1;k=edges[k].next)
    {
        int v = edges[k].v;
        if(dp[v] == -1) dfs(v);
        dp[u] = max(dp[u],dp[v] + 1);
    }
}
bool findpath(int u)
{
    vis[u] = -1;
    if(dp[u] == 0) return true;
    for(int k = head[u];k != -1;k=edges[k].next)
    {
        int v = edges[k].v;
        if(vis[v] == -1) continue;
        if(dp[v] + 1 == dp[u])
        {
            if(findpath(v)) return true;
        }
    }
    vis[u] = 0;
    return false;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(head,0xff,sizeof(head));
    nEdge = -1;
    int N = 0;
    for(int i = 0;i < n;++i)
    {
        scanf("%s",a[i]);
        for(int j = 0;j < m;++j)
        {
            if(a[i][j] != '#')
                vec[i][j] = ++N;
        }
    }
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < m;++j)
        {
            if(a[i][j] == '#') continue;
            int dir = getDir(a[i][j]);
            int x = i + dirx[dir];
            int y = j + diry[dir];
            if(a[x][y] != '#')
                AddEdges(vec[i][j],vec[x][y]);
        }
    }
    int ival = 0;
    bool flag = true;
    for(int i = 1;i <= N;++i)
        if(!vis[i])
        {
            flag &= DFS(i,++ival);
            if(!flag) break;
        }
    if(!flag) puts("-1");
    else
    {
        memset(dp,0xff,sizeof(dp));
        int maxv = -1;
        for(int i = 1;i <= N;++i)
        {
            if(dp[i] == -1)
            {
                dfs(i);
            }
            maxv = max(maxv,dp[i]);
        }
        int cnt = 0;
        for(int i = 1;i <= N;++i)
        {
            if(dp[i] == maxv && vis[i] != -1)
            {
                if(findpath(i))
                {
                    cnt++;
                    if(cnt == 2) break;
                }
            }
        }
        maxv++;
        if(cnt == 2) printf("%d\n",maxv*2);
        else printf("%d\n",maxv+max(0,maxv-1));
    }
    return 0;
}

