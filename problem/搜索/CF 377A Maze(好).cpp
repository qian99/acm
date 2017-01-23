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
const int maxm=maxn*maxn;
const int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char maze[maxn][maxn];
int dfn[maxn][maxn],dfs_clock;
int n,m,k,tot;
void dfs(int x,int y)
{
    tot++;
    dfn[x][y]=++dfs_clock;
    int dx,dy;
    for(int i=0;i<4;++i)
    {
        dx=x+dir[i][0];
        dy=y+dir[i][1];
        if(dx>=0&&dy>=0&&dx<n&&dy<m&&maze[dx][dy]=='.'&&!dfn[dx][dy])
            dfs(dx,dy);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;++i)
        scanf("%s",maze[i]);
    memset(dfn,0,sizeof(dfn));
    dfs_clock=tot=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(maze[i][j]=='.'&&!dfn[i][j])
                dfs(i,j);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(dfn[i][j]>tot-k)
                printf("X");
            else printf("%c",maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}
