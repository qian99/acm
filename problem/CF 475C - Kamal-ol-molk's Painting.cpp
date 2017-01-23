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
const int maxn = 1000 + 10;
char a[maxn][maxn],b[maxn][maxn];
int n,m,ans;
int sx = -1,sy = -1,ry,rx;
void copymat()
{
    for(int i = 0;i < n;++i)
        for(int j = 0;j < m;++j)
            b[i][j] = a[i][j];
}
bool checkrow(int x,int L,int R)
{
    for(int i = L;i <= R;++i)
        if(b[x][i] != 'X') return false;
    return true;
}
bool checkcol(int y,int L,int R)
{
    for(int i = L;i <= R;++i)
        if(b[i][y] != 'X') return false;
    return true;
}
bool paint(int x,int y,int H,int W)
{
    if(b[x][y] != 'X')
    {
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j)
            {
                if(b[i][j] == 'X')
                    return false;
            }
        return true;
    }
    ///right -> down
    int dy = y;
    while(dy < m && b[x][dy] == 'X') dy++;
    dy--;
    if(y + W - 1 < dy)
    {
        for(int i = y;i < dy - W + 1;++i)
        {
            if(!checkcol(i,x,x + H - 1)) return false;
            for(int j = x;j < x + H;++j)
                b[j][i] = '.';
        }
        return paint(x,dy - W + 1,H,W);
    }
    ///down -> right
    int dx = x;
    while(dx < n && b[dx][y] == 'X') dx++;
    dx--;
    if(x + H - 1 < dx)
    {
        for(int i = x;i < dx - H + 1;++i)
        {
            if(!checkrow(i,y,y + W - 1)) return false;
            for(int j = y;j < y + W;++j)
                b[i][j] = '.';
        }
        return paint(dx - H + 1,y,H,W);
    }
    ///no move
    for(int i = x;i < x + H;++i)
    {
        if(!checkrow(i,y,y + W - 1)) return false;
        for(int j = y;j < y + W ;++j)
            b[i][j] = '.';
    }
    return paint(0,0,H,W);
}
void solve()
{
    ry = sy;
    while(ry < m && a[sx][ry] == 'X') ry++;
    ry--;
    int dx = sx;
    int H,W,px = -1;
    if(ry + 1 < m && a[dx][ry + 1] != 'X') px = dx;
    while(dx + 1 < n && a[dx + 1][sy] == 'X')
    {
        if(!checkrow(dx + 1,sy,ry)) return ;
        if(ry + 1 < m && a[dx + 1][ry + 1] != 'X')
        {
            px = dx + 1;
        }
        dx++;
    }
    if(px == -1) return ;
    H = dx - px;
    W = ry - sy + 1;
    if(H <= 0 || W <= 0) return ;
    if(paint(sx,sy,H,W))
        ans = min(ans,H*W);
}
void solve2()
{
    rx = sx;
    while(rx < n && a[rx][sy] == 'X') rx++;
    rx--;
    int dy = sy;
    int H,W,py = -1;
    if(rx + 1 < n && a[rx + 1][dy] != 'X') py = dy;
    while(dy + 1 < n && a[sx][dy + 1] == 'X')
    {
        if(!checkcol(dy + 1,sx,rx)) return ;
        if(rx + 1 < n && a[rx + 1][dy + 1] != 'X')
        {
            py = dy + 1;
        }
        dy++;
    }
    if(py == -1) return ;
    H = rx - sx + 1;
    W = dy - py;
    if(H <= 0 || W <= 0) return ;
    if(paint(sx,sy,H,W))
        ans = min(ans,H*W);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++i)
        scanf("%s",a[i]);
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < m;++j)
            if(a[i][j] == 'X')
            {
                sx = i;
                sy = j;
                break;
            }
        if(sx != -1) break;
    }
    ans = inf;
    copymat();
    solve();
    copymat();
    solve2();
    copymat();
    int py = sy;
    while(py < m && a[sx][py] == 'X') py++;
    py--;
    if(paint(sx,sy,1,py - sy + 1))
        ans = min(ans,py - sy + 1);
    copymat();
    int px = sx;
    while(px < n && a[px][sy] == 'X') px++;
    px--;
    if(paint(sx,sy,px - sx + 1,1))
        ans = min(ans,px - sx + 1);
    if(ans == inf) ans = -1;
    printf("%d\n",ans);
    return 0;
}

