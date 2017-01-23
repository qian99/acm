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
using namespace std;
const int maxn=5000+10;
const int move[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
struct Node
{
    int x,y;
    int cost;
};
struct Point
{
    int x,y;
};
char maze[maxn][maxn];
bool vis[maxn][maxn];
Point pt[maxn/10],s,t;
int n,m,ct,pc;
bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m&&!vis[x][y]&&maze[x][y]!='#';
}
int bfs()
{
    memset(vis,0,sizeof(vis));
    vis[s.x][s.y]=true;
    queue<Node>q;
    Node tmp,node;
    node.x=s.x;node.y=s.y;node.cost=0;
    q.push(node);
    int dx,dy;
    while(!q.empty())
    {
        node=q.front();q.pop();
        if(node.x==t.x&&node.y==t.y)
          return node.cost;
        for(int i=0;i<4;++i)
        {
            dx=node.x+move[i][0];
            dy=node.y+move[i][1];
            if(check(dx,dy))
            {
                if(maze[dx][dy]=='P')
                {
                    for(int j=0;j<pc;++j)
                    {
                        vis[pt[j].x][pt[j].y]=true;
                        for(int k=0;k<4;++k)
                        {
                            dx=pt[j].x+move[k][0];
                            dy=pt[j].y+move[k][1];
                            if(check(dx,dy)&&maze[dx][dy]!='P')
                            {
                                vis[dx][dy]=true;
                                tmp.x=dx;tmp.y=dy;
                                if(maze[dx][dy]=='*') tmp.cost=node.cost+ct;
                                else tmp.cost=node.cost;
                                q.push(tmp);
                            }
                        }
                    }
                }
                else
                {
                    vis[dx][dy]=true;
                    tmp.x=dx;tmp.y=dy;
                    if(maze[dx][dy]=='*') tmp.cost=node.cost+ct;
                    else tmp.cost=node.cost;
                    q.push(tmp);
                }
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&ct))
    {
        pc=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<m;++j)
              if(maze[i][j]=='Y')
                s.x=i,s.y=j;
              else if(maze[i][j]=='C')
                t.x=i,t.y=j;
              else if(maze[i][j]=='P')
                pt[pc].x=i,pt[pc++].y=j;
        }
        int ans=bfs();
        if(ans==-1) printf("Damn teoy!\n");
        else printf("%d\n",ans);
    }
    return 0;
}
