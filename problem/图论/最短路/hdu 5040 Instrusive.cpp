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
const int maxn = 500 + 10;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
const int dxz[4] = {-1,1,1,-1};
const int dyz[4] = {1,1,-1,-1};
char mat[maxn][maxn];
int c[maxn][maxn],d[maxn][maxn],sx,sy,ex,ey,n;
void cal(int x,int y,char cc)
{
    c[x][y] = (1<<4) - 1;
    int fdir;
    if(cc == 'N') fdir = 0;
    else if(cc == 'E') fdir = 1;
    else if(cc == 'S') fdir = 2;
    else fdir = 3;
    int dx,dy;
    for(int i = 0;i < 4;++i)
    {
        dx = x + dirx[(i + fdir)%4];
        dy = y + diry[(i + fdir)%4];
        if(dx >= 0 && dx < n && dy >= 0 && dy < n && mat[x][y] != '#')
        {
            c[dx][dy] |= (1<<i);
        }
//        dx = x + dxz[(i + fdir)%4];
//        dy = y + dyz[(i + fdir)%4];
//        if(dx >= 0 && dx < n && dy >= 0 && dy < n && mat[x][y] != '#')
//        {
//            c[dx][dy] |= (1<<i);
//        }
    }
}
struct Node
{
    int x,y;
    Node(int x = 0,int y = 0):x(x),y(y){}
};
bool inq[maxn][maxn];
void spfa()
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[sx][sy] = 0;
    queue<Node>q;
    q.push(Node(sx,sy));
    int x,y,dx,dy;
    int state,snext;
    Node node;
    while(!q.empty())
    {
        node = q.front();q.pop();
        x = node.x;
        y = node.y;
        inq[x][y] = false;
//        snext = 1<<((d[x][y] + 1)%4);
        for(int i = 0;i < 4;++i)
        {
            state = 1<<((d[x][y])%4);
            dx = x + dirx[i];
            dy = y + diry[i];
            if(dx >= 0 && dx < n && dy >= 0 && dy < n && mat[dx][dy] != '#')
            {
                if((state & c[dx][dy]) || (state & c[x][y]) )
                {
                    if(d[dx][dy] > d[x][y] + 3)
                    {
                        d[dx][dy] = d[x][y] + 3;
                        if(!inq[dx][dy]){inq[dx][dy] = true;q.push(Node(dx,dy));}
                    }
                }
                else
                {
//                    snext = 1<<(d[x][y]%4);
//                    if(!(snext & c[dx][dy]))
//                    {
                        if(d[dx][dy] > d[x][y] + 1)
                        {
                            d[dx][dy] = d[x][y] + 1;
                            if(!inq[dx][dy]) {inq[dx][dy] = true;q.push(Node(dx,dy));}
                        }
//                    }
                }
                state = 1<<((d[x][y] + 1)%4);
                snext = 1<<((d[x][y] + 1)%4);
                if((!(state & c[x][y])) && (!(snext & c[dx][dy])))
                {
                    if(d[dx][dy] > d[x][y] + 2)
                    {
                        d[dx][dy] = d[x][y] + 2;
                        if(!inq[dx][dy]) {inq[dx][dy] = true;q.push(Node(dx,dy));}
                    }
                }
            }
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        memset(c,0,sizeof(c));
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%s",mat[i]);
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == 'M')
                    sx = i,sy = j;
                else if(mat[i][j] == 'T')
                    ex = i,ey = j;
                else if(mat[i][j] == 'N' || mat[i][j] == 'S' || mat[i][j] == 'W' || mat[i][j] == 'E')
                {
                    cal(i,j,mat[i][j]);
                }
            }
        }
        spfa();
        int ans = d[ex][ey];
        if(ans == inf) ans = -1;
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}