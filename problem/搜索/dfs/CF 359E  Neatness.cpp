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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
const int maxm=1000000*3+10;
const int move[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
const char dir[4]={'L','D','R','U'};
int maze[maxn][maxn],n,cnt;
char res[maxm];
bool vis[maxn][maxn];
void dfs(int x,int y)
{
    vis[x][y]=true;
    if(maze[x][y]==0)
    {
        maze[x][y]=1;
        res[cnt++]='1';
    }
    for(int i=0;i<4;++i)
    {
        int dx=x+move[i][0],dy=y+move[i][1];
        while(dx>=1&&dx<=n&&dy>=1&&dy<=n)
        {
            if(maze[dx][dy])
            {
                if(!vis[dx][dy])
                {
                    res[cnt++]=dir[i];
                    dfs(x+move[i][0],y+move[i][1]);
                    res[cnt++]=dir[(i+2)%4];
                }
                break;
            }
            dx+=move[i][0],dy+=move[i][1];
        }
    }
    maze[x][y]=0;
    res[cnt++]='2';
}
bool canch()
{
    for(int i=1;i<=n;++i)
      for(int j=1;j<=n;++j)
        if(maze[i][j]) return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y;
    while(~scanf("%d%d%d",&n,&x,&y))
    {
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;++i)
          for(int j=1;j<=n;++j)
            scanf("%d",&maze[i][j]);
        cnt=0;
        dfs(x,y);
        if(canch())
        {
            printf("YES\n");
            res[cnt]='\0';
            printf("%s\n",res);
        }
        else printf("NO\n");
    }
    return 0;
}
