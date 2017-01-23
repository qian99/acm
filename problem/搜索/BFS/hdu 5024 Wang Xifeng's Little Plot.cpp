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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
const int dirx[8] = {-1,0,1,1,1,0,-1,-1};
const int diry[8] = {1,1,1,0,-1,-1,-1,0};
char mat[maxn][maxn];
int maxmove[maxn][maxn][8],n;
int qx[maxn*maxn],qy[maxn*maxn];
void cal(int x,int y,int dir)
{
    int tail = 0,base = 0;
    qx[tail] = x;
    qy[tail++] = y;
    int dx,dy;
    for(int i = 0;i < tail;++i)
    {
        x = qx[i];
        y = qy[i];
        dx = x + dirx[dir];
        dy = y + diry[dir];
        if(dx >= 0 && dx < n && dy >= 0 && dy < n && mat[dx][dy] == '.')
        {
            if(maxmove[dx][dy][dir] != -1)
            {
                base = maxmove[dx][dy][dir];
                break;
            }
            qx[tail] = dx;
            qy[tail++] = dy;
        }
    }
    for(int i = tail - 1;i >= 0; --i)
    {
        x = qx[i];
        y = qy[i];
        maxmove[x][y][dir] = ++base;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        memset(maxmove,0xff,sizeof(maxmove));
        for(int i = 0;i < n;++i)
            scanf("%s",mat[i]);
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == '#') continue;
                for(int k = 0;k < 8;++k)
                    cal(i,j,k);
            }
        int ans = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
            {
                ans = max(ans,maxmove[i][j][0] + maxmove[i][j][2] - 1);
                ans = max(ans,maxmove[i][j][1] + maxmove[i][j][3] - 1);
                ans = max(ans,maxmove[i][j][2] + maxmove[i][j][4] - 1);
                ans = max(ans,maxmove[i][j][3] + maxmove[i][j][5] - 1);
                ans = max(ans,maxmove[i][j][4] + maxmove[i][j][6] - 1);
                ans = max(ans,maxmove[i][j][5] + maxmove[i][j][7] - 1);
                ans = max(ans,maxmove[i][j][6] + maxmove[i][j][0] - 1);
                ans = max(ans,maxmove[i][j][7] + maxmove[i][j][1] - 1);
            }
        printf("%d\n",ans);
    }
    return 0;
}