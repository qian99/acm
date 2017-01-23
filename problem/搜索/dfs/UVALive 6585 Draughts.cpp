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
const int dirx[4] = {-1,-1,1,1};
const int diry[4] = {1,-1,1,-1};
const int n = 10;
char board[11][11];
int ans;
void dfs(int x,int y,int cnt)
{
    if(cnt > ans) ans = cnt;
    int dx,dy,ex,ey;
    for(int i = 0;i < 4;++i)
    {
        dx = x + dirx[i];
        dy = y + diry[i];
        if(dx >= 0 && dx < n && dy >= 0 && dy < n && board[dx][dy] == 'B')
        {
            ex = dx + dirx[i];
            ey = dy + diry[i];
            if(ex >= 0 && ex < n && ey >= 0 && ey < n && board[ex][ey] == '#')
            {
                board[x][y] = '#';
                board[dx][dy] = '#';
                board[ex][ey] = 'W';
                dfs(ex,ey,cnt + 1);
                board[x][y] = 'W';
                board[dx][dy] = 'B';
                board[ex][ey] = '#';
            }
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        for(int i = 0;i < 10;++i)
            scanf("%s",board[i]);
        ans = 0;
        for(int i = 0;i < 10;++i)
            for(int j = 0;j < 10;++j)
            {
                if(board[i][j] == 'W')
                    dfs(i,j,0);
            }
        printf("%d\n",ans);
    }
    return 0;
}

