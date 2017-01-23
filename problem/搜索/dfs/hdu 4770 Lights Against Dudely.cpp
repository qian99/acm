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
const int maxn=200+10;
const int dir[4][3][2]={{{-1,0},{0,1},{0,0}},{{1,0},{0,1},{0,0}},{{0,-1},{1,0},{0,0}},{{0,-1},{-1,0},{0,0}}};
char maze[maxn][maxn];
int vis[maxn][maxn],n,m,cnt;
int pt[20][2],ans;
bool flag[maxn][maxn];
bool check(int x,int y,int w)
{
    int dx,dy;
    for(int i=0;i<3;++i)
    {
        dx=x+dir[w][i][0];
        dy=y+dir[w][i][1];
        if(dx<0||dx>=n||dy<0||dy>=m) continue;
        if(maze[dx][dy]=='#')
          return false;
    }
    return true;
}
void dfs(int i,int step,int us)
{
    if(i==cnt)
    {
        for(int j=0;j<cnt;++j)
          if(!vis[pt[j][0]][pt[j][1]]) return ;
        ans=min(step,ans);
        return ;
    }
    int x=pt[i][0];
    int y=pt[i][1];
    int dx,dy;
    if(check(x,y,0))
    {
        flag[x][y]=true;
        for(int j=0;j<3;++j)
        {
            dx=x+dir[0][j][0];
            dy=y+dir[0][j][1];
            if(dx<0||dx>=n||dy<0||dy>=m) continue;
            vis[dx][dy]++;
        }
        dfs(i+1,step+1,us);
        for(int j=0;j<3;++j)
        {
            dx=x+dir[0][j][0];
            dy=y+dir[0][j][1];
            if(dx<0||dx>=n||dy<0||dy>=m) continue;
            vis[dx][dy]--;
        }
        flag[x][y]=false;
    }
    for(int k=1;k<4;++k)
    {
        if(us) break;
        flag[x][y]=true;
        if(check(x,y,k))
        {

            for(int j=0;j<3;++j)
            {
                dx=x+dir[k][j][0];
                dy=y+dir[k][j][1];
                if(dx<0||dx>=n||dy<0||dy>=m) continue;
                vis[dx][dy]++;
            }
            dfs(i+1,step+1,1);
            for(int j=0;j<3;++j)
            {
                dx=x+dir[k][j][0];
                dy=y+dir[k][j][1];
                if(dx<0||dx>=n||dy<0||dy>=m) continue;
                vis[dx][dy]--;
            }
        }
        flag[x][y]=false;
    }
    dfs(i+1,step,us);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        cnt=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<m;++j)
            {
                if(maze[i][j]=='.')
                  pt[cnt][0]=i,pt[cnt++][1]=j;
            }
        }
        memset(vis,0,sizeof(vis));
        memset(flag,0,sizeof(flag));
        ans=inf;
        dfs(0,0,0);
        if(ans==inf) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
