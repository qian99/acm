#include <iostream>
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
const int maxn=30;
char maze[maxn][maxn];
bool vis[maxn][maxn][4][5];
const int dirt[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int m,n;
struct Data
{
    int x,y,color,dir,step;
};
bool check(int x,int y,int color,int dir)
{
    return x>=0&&x<m&&y>=0&&y<n&&maze[x][y]!='#'&&!vis[x][y][dir][color];
}
int bfs(int sx,int sy,int ex,int ey)
{
    memset(vis,0,sizeof(vis));
    vis[sx][sy][0][0]=true;
    Data dt,dd;
    queue<Data>q;
    dt.x=sx;dt.y=sy;dt.color=dt.dir=dt.step=0;
    q.push(dt);
    while(!q.empty())
    {
        dt=q.front();
        q.pop();
        if(dt.x==ex&&dt.y==ey&&dt.color==0) return dt.step;
        dd.x=dt.x;dd.y=dt.y;
        dd.color=dt.color;
        dd.dir=(dt.dir+1)%4;
        dd.step=dt.step+1;
        if(check(dd.x,dd.y,dd.color,dd.dir))
        {
            vis[dd.x][dd.y][dd.dir][dd.color]=true;
            q.push(dd);
        }
        dd.dir=(dt.dir+3)%4;
        if(check(dd.x,dd.y,dd.color,dd.dir))
        {
            vis[dd.x][dd.y][dd.dir][dd.color]=true;
            q.push(dd);
        }
        dd.x=dt.x+dirt[dt.dir][0];
        dd.y=dt.y+dirt[dt.dir][1];
        dd.dir=dt.dir;
        dd.color=(dt.color+1)%5;
        if(check(dd.x,dd.y,dd.color,dd.dir))
        {
            vis[dd.x][dd.y][dd.dir][dd.color]=true;
            q.push(dd);
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    int sx,sy,ex,ey;
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0&&n==0) break;
        tcase++;
        for(int i=0;i<m;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<n;++j)
            {
                if(maze[i][j]=='S')
                {
                    sx=i;
                    sy=j;
                }
                if(maze[i][j]=='T')
                {
                    ex=i;
                    ey=j;
                }
            }
        }
        int res=bfs(sx,sy,ex,ey);
        if(tcase>1) printf("\n");
        printf("Case #%d\n",tcase);
        if(res==-1)
          printf("destination not reachable\n");
        else
          printf("minimum time = %d sec\n",res);
    }
    return 0;
}
