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
typedef long long ll;
const int maxn=1<<8;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};
struct Node
{
    int x,y,st,sb;
    Node(){};
    Node(int xx,int yy,int tt,int bb){x=xx;y=yy;st=tt;sb=bb;}
};
int d[25][25][maxn][maxn],bomb[10][2],t[10][2];
int n,m,bnt,tnt,sx,sy,val[10];
char mz[25][25];
inline bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m&&mz[x][y]=='.';
}
void bfs()
{
    queue<Node>q;
    d[sx][sy][0][0]=0;
    q.push(Node(sx,sy,0,0));
    Node node;
    int dx,dy,dt,db;
    while(!q.empty())
    {
        node=q.front();q.pop();
        for(int i=0;i<4;++i)
        {
            dx=node.x+dirx[i];
            dy=node.y+diry[i];
            if(!check(dx,dy)) continue;
            dt=node.st;db=node.sb;
            if(i&1)
            {
                for(int j=0;j<tnt;++j)
                {
                    if(i==1&&t[j][1]==dy&&t[j][0]>node.x)
                        dt^=(1<<j);
                    else if(i==3&&t[j][1]==node.y&&t[j][0]>node.x)
                        dt^=(1<<j);
                }
                for(int j=0;j<bnt;++j)
                {
                    if(i==1&&bomb[j][1]==dy&&bomb[j][0]>node.x)
                        db^=(1<<j);
                    else if(i==3&&bomb[j][1]==node.y&&bomb[j][0]>node.x)
                        db^=(1<<j);
                }
            }
            if(d[dx][dy][dt][db]!=-1) continue;
            d[dx][dy][dt][db]=d[node.x][node.y][node.st][node.sb]+1;
            q.push(Node(dx,dy,dt,db));
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    memset(d,0xff,sizeof(d));
    bnt=tnt=0;
    for(int i=0;i<n;++i)
    {
        scanf("%s",mz[i]);
        for(int j=0;j<m;++j)
        {
            if(mz[i][j]=='S') {sx=i,sy=j;mz[i][j]='.';}
            else if(mz[i][j]>='1'&&mz[i][j]<='8')
            {t[(int)mz[i][j]-'0'-1][0]=i;t[(int)mz[i][j]-'0'-1][1]=j;tnt++;}
            else if(mz[i][j]=='B') {bomb[bnt][0]=i;bomb[bnt++][1]=j;}
        }
    }
    for(int i=0;i<tnt;++i)
        scanf("%d",&val[i]);
    bfs();
    int ans=0;
    for(int i=1;i<(1<<tnt);++i)
    {
        int sum=0;
        if(d[sx][sy][i][0]==-1) continue;
        for(int j=0;j<tnt;++j)
            if(i&(1<<j))
               sum+=val[j];
        sum-=d[sx][sy][i][0];
        ans=max(ans,sum);
    }
    printf("%d\n",ans);
    return 0;
}
