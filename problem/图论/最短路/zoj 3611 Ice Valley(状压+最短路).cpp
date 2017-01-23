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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500+10;
const int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
const char dc[4]={'D','R','U','L'};
char maze[maxn][maxn];
bool vis[maxn][maxn],inq[155][1<<11];
int cs[maxn][maxn],ct[maxn][maxn],indx[maxn][maxn],val[155],msk[155];
int d[155][1<<11],n,m,sx,sy,ex,ey,tot,cnt;
struct Edge
{
    int v,w,next;
    Edge (){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxn<<2];
struct Node
{
    int u,st;
    Node (){}
    Node(int u,int st):u(u),st(st){}
};
int head[155],nEdge;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
}
bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
int dfs(int x,int y)
{
    int i;
    vis[x][y]=true;
    for(i=0;i<4;++i)
    {
       if(maze[x][y]==dc[i])
            break;
    }
    int dx=x+dir[i][0];
    int dy=y+dir[i][1];
    if(!check(dx,dy)) return -1;
    if(maze[dx][dy]=='W'||maze[dx][dy]=='#') return ct[dx][dy]=cs[dx][dy]=-1;
    if(maze[dx][dy]=='0'||maze[dx][dy]=='$')
    {
        cs[x][y]=indx[dx][dy];
        ct[x][y]=1;
        return ct[x][y]+1;
    }
    if(vis[dx][dy])
    {
        cs[x][y]=cs[dx][dy];
        if(cs[x][y]==-1) return ct[x][y]=-1;
        ct[x][y]=1+ct[dx][dy];
        return ct[x][y]+1;
    }
    ct[x][y]=dfs(dx,dy);
    if(ct[x][y]==-1) return cs[x][y]=-1;
    else cs[x][y]=cs[dx][dy];
    return ct[x][y]+1;
}
void build()
{
    memset(vis,0,sizeof(vis));
    memset(val,0,sizeof(val));
    tot=cnt=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(maze[i][j]=='0'||maze[i][j]=='$')
            {
                indx[i][j]=++tot;
                if(maze[i][j]=='$') {val[tot]=1;msk[tot]=cnt++;}
                vis[i][j]=true;
            }
            else if(maze[i][j]=='W'||maze[i][j]=='#')
                vis[i][j]=true;
    memset(cs,0xff,sizeof(cs));
    memset(ct,0,sizeof(ct));
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(!vis[i][j])
                dfs(i,j);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int dx,dy;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            if(maze[i][j]!='0'&&maze[i][j]!='$') continue;
            for(int k=0;k<4;++k)
            {
                dx=i+dir[k][0];
                dy=j+dir[k][1];
                if(check(dx,dy)&&maze[dx][dy]!='#'&&maze[dx][dy]!='W')
                {
                    if(maze[dx][dy]=='0'||maze[dx][dy]=='$')
                    {
                        AddEdges(indx[i][j],indx[dx][dy],1);
                        continue;
                    }
                    if(cs[dx][dy]==-1) continue;
                    AddEdges(indx[i][j],cs[dx][dy],ct[dx][dy]+1);
                }
            }
        }
}
void spfa(int s,int t)
{
    queue<Node>q;
    memset(inq,0,sizeof(inq));
    memset(d,0x3f,sizeof(d));
    d[s][0]=0;
    q.push(Node(s,0));
    Node node;
    while(!q.empty())
    {
        node=q.front();q.pop();
        int u=node.u,v,state=node.st;
        inq[u][state]=false;
        int tmp;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            state=node.st;
            if(val[v])
            {
                if(state&(1<<msk[v])) tmp=d[u][state]+edges[k].w;
                else tmp=d[u][state]+edges[k].w+2;
                state|=(1<<msk[v]);
            }
            else tmp=d[u][state]+edges[k].w;
            if(d[v][state]>tmp)
            {
                d[v][state]=tmp;
                if(!inq[v][state]) {inq[v][state]=true;q.push(Node(v,state));}
            }
        }
    }
}
int cal(int x)
{
    int y=0;
    while(x)
    {
        y++;
        x=x&(x-1);
    }
    return y;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;++i)
            scanf("%s",maze[i]);
        scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
        sx--;sy--;ex--;ey--;
        build();
        int S=indx[sx][sy],T=indx[ex][ey];
        spfa(S,T);
        int mint=inf,maxget=-1,tmp;
        for(int i=(1<<cnt)-1;i>=0;--i)
        {
            if(d[T][i]==inf) continue;
            tmp=cal(i);
            if(tmp<maxget) continue;
            if(tmp>maxget)
            {
                mint=d[T][i];
                maxget=tmp;
            }
            else if(tmp==maxget)
                mint=min(mint,d[T][i]);
        }
        if(mint==inf) mint=-1;
        printf("%d\n",mint);
    }
    return 0;
}
