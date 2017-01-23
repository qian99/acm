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
const int dirx[4] = {1,-1,0,0};
const int diry[4] = {0,0,1,-1};
char mat[maxn][maxn];
int d[maxn][maxn][10][1<<5],n,m,sx,sy,ex,ey;
int snk[maxn][maxn],snt;
struct Node
{
    int x,y,key,msk;
    Node(int x = 0,int y = 0,int key = 0,int msk = 0):x(x),y(y),key(key),msk(msk){}
};
void bfs()
{
    queue<Node>q;
    q.push(Node(sx,sy,0,0));
    d[sx][sy][0][0] = 0;
    Node node;
    int dx,dy,k,mk,cost;
    while(!q.empty())
    {
        node = q.front();q.pop();
        for(int i = 0;i < 4;++i)
        {
            dx = node.x + dirx[i];
            dy = node.y + diry[i];
            if(dx < 0 || dx >= n || dy < 0 || dy >= n || mat[dx][dy] == '#')
                continue;
            k = node.key;
            mk = node.msk;
            cost = d[node.x][node.y][k][mk] + 1;
            if(mat[dx][dy] >= '1' && mat[dx][dy] <= '9')
            {
                if(node.key + 1 == mat[dx][dy] - '0')
                    k++;
            }
            if(mat[dx][dy] == 'S')
            {
                if(!(snk[dx][dy] & mk))
                {
                    cost++;
                    mk |= snk[dx][dy];
                }
            }
            if(d[dx][dy][k][mk] == -1)
            {
                d[dx][dy][k][mk] = cost;
                q.push(Node(dx,dy,k,mk));
            }
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        snt = 0;
        memset(snk,0,sizeof(snk));
        for(int i = 0;i < n;++i)
        {
            scanf("%s",mat[i]);
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == 'K')
                    sx = i,sy = j;
                if(mat[i][j] == 'T')
                    ex = i,ey = j;
                if(mat[i][j] == 'S')
                    snk[i][j] |= 1<<snt,snt++;
            }
        }
        memset(d,0xff,sizeof(d));
        bfs();
        int ans = inf;
        for(int i = 0;i < (1<<snt);++i)
            if(d[ex][ey][m][i] != -1)
                ans = min(ans,d[ex][ey][m][i]);
        if(ans == inf)
            puts("impossible");
        else
            printf("%d\n",ans);
    }
    return 0;
}