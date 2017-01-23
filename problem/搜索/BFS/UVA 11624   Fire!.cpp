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
const int maxn=1000+10;
const int move[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int firetime[maxn][maxn];
bool vis[maxn][maxn];
char maze[maxn][maxn];
int m,n;
struct Fire
{
    int x,y,time;
};
queue<Fire>Firepoint;
bool check(int x,int y)
{
    return x>=0&&x<m&&y>=0&&y<n&&maze[x][y]!='#';
}
bool getout(int x,int y)
{
    return x==m-1||y==n-1||x==0||y==0;
}
void getfiretimes()
{
    Fire ft,ff;
    int px,py;
    while(!Firepoint.empty())
    {
        ft=Firepoint.front();
        Firepoint.pop();
        for(int i=0;i<4;++i)
        {
            px=ft.x+move[i][0];
            py=ft.y+move[i][1];
            if(check(px,py)&&!vis[px][py])
            {
                vis[px][py]=true;
                firetime[px][py]=ft.time+1;
                ff.x=px;ff.y=py;
                ff.time=ft.time+1;
                Firepoint.push(ff);
            }
        }
    }
}
int bfs(int sx,int sy)
{
    memset(vis,0,sizeof(vis));
    Fire ft,ff;
    queue<Fire>q;
    vis[sx][sy]=true;
    ft.x=sx;ft.y=sy;
    ft.time=0;
    q.push(ft);
    while(!q.empty())
    {
        ft=q.front();
        q.pop();
        if(getout(ft.x,ft.y)) return ft.time+1;
        int px,py;
        for(int i=0;i<4;++i)
        {
            px=ft.x+move[i][0];
            py=ft.y+move[i][1];
            if(check(px,py)&&!vis[px][py]&&firetime[px][py]>ft.time+1)
            {
                vis[px][py]=true;
                ff.x=px;ff.y=py;
                ff.time=ft.time+1;
                q.push(ff);
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        Fire ff;
        int sx,sy;
        for(int i=0;i<m;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<n;++j)
            {
                firetime[i][j]=inf;
                vis[i][j]=false;
                if(maze[i][j]=='F')
                {
                    ff.x=i;ff.y=j;
                    ff.time=0;
                    Firepoint.push(ff);
                    vis[i][j]=true;
                }
                else if(maze[i][j]=='J')
                {
                    sx=i;
                    sy=j;
                }
            }
        }
        getfiretimes();
        int res=bfs(sx,sy);
        if(res==-1)
          printf("IMPOSSIBLE\n");
        else
          printf("%d\n",res);
    }
    return 0;
}
