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
const int maxn=100+10;
const int move[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int vis[maxn][maxn][1<<4],n,m;
int tar[4][2],k;
char maze[maxn][maxn];
struct Node
{
    int x,y,step;
    int state;
};
inline bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m&&maze[x][y]!='#';
}
int bfs(int sx,int sy)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<k;++i) tar[i][0]--,tar[i][1]--;
    queue<Node>q;
    Node node,tmp;
    node.x=sx,node.y=sy;
    node.step=0;
    int st=0;
    for(int i=0;i<k;++i)
    {
        if(sx==tar[i][0]&&sy==tar[i][1])
          st|=(1<<i);
    }
    node.state=st;
    q.push(node);
    vis[sx][sy][st]=true;
    while(!q.empty())
    {
        node=q.front();q.pop();
        if(node.state==((1<<k)-1)) return node.step;
        int dx,dy;
        for(int i=0;i<4;++i)
        {
            dx=node.x+move[i][0];
            dy=node.y+move[i][1];
            st=node.state;
            if(!check(dx,dy)) continue;
            for(int j=0;j<k;++j)
              if(dx==tar[j][0]&&dy==tar[j][1])
                 st|=(1<<j);
            if(!vis[dx][dy][st])
            {
                vis[dx][dy][st]=true;
                tmp.x=dx;tmp.y=dy;
                tmp.step=node.step+1;
                tmp.state=st;
                q.push(tmp);
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int sx,sy;
        for(int i=0;i<n;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<m;++j)
              if(maze[i][j]=='@')
                sx=i,sy=j;
        }
        scanf("%d",&k);
        for(int i=0;i<k;++i)
          scanf("%d%d",&tar[i][0],&tar[i][1]);
        int ans=bfs(sx,sy);
        printf("%d\n",ans);
    }
    return 0;
}
