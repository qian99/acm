#include<iostream>
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
const int maxn=100+10;
const int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
char maze[maxn][maxn];
bool vis[maxn][maxn];
int m,n;
bool check(int x,int y)
{
    return x>=0&&x<m&&y>=0&&y<n&&maze[x][y]=='@'&&!vis[x][y];
}
void dfs(int x,int y)
{
    vis[x][y]=true;
    for(int i=0;i<8;++i)
    {
        int dx=x+dir[i][0];
        int dy=y+dir[i][1];
        if(check(dx,dy))
        {
            dfs(dx,dy);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0) break;
        for(int i=0;i<m;++i)
        {
            scanf("%s",maze[i]);
        }
        memset(vis,0,sizeof(vis));
        int cnt=0;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(!vis[i][j]&&maze[i][j]=='@')
                {
                    dfs(i,j);
                    cnt++;
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}

