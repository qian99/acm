#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=10;
bool vis[maxn][maxn][maxn][maxn][4][4];
//bool vis2[maxn][maxn][4];
char maze[15][15];
int move[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
bool check(int x,int y)
{
    return x>=0&&x<maxn&&y>=0&&y<maxn&&maze[x][y]!='*';
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(vis,false,sizeof(vis));
        //memset(vis2,false,sizeof(vis2));
        int mx,my,cx,cy;
        int mdir=0,cdir=0;
        for(int i=0;i<maxn;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<maxn;++j)
            {
                if(maze[i][j]=='m')
                {
                    mx=i;
                    my=j;
                }
                if(maze[i][j]=='c')
                {
                    cx=i;
                    cy=j;
                }
            }
        }
        vis[mx][my][cx][cy][0][0]=true;
        //vis2[cx][cy][0]=true;
        int px,py,step=0;
        bool find=true;
        while(!((mx==cx)&&(my==cy)))
        {
            px=mx+move[mdir][0];
            py=my+move[mdir][1];
            if(check(px,py))
            {
                mx+=move[mdir][0];
                my+=move[mdir][1];
            }
            else
            {
                mdir=(mdir+1)%4;
            }
            px=cx+move[cdir][0];
            py=cy+move[cdir][1];
            if(check(px,py))
            {
                cx+=move[cdir][0];
                cy+=move[cdir][1];
            }
            else
            {
                cdir=(cdir+1)%4;
            }
            if(vis[mx][my][cx][cy][mdir][cdir])
            {
                find=false;
                break;
            }
            vis[mx][my][cx][cy][mdir][cdir]=true;
            step++;
        }
        if(find)
        {
            printf("%d\n",step);
        }
        else
        {
            printf("0\n");
        }
    }
    return 0;
}
