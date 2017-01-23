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
const int maxn=100+10;
struct Rally
{
    int index,pos;
    bool operator < (const Rally & a) const
    {
        return index<a.index;
    }
};
const int move[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int m,n;
char maze[maxn][maxn];
Rally rally[maxn];
int Treasure[maxn*maxn];
int dist[maxn][maxn*maxn];
bool vis[maxn*maxn];
int link[maxn*maxn];
vector<int>G[maxn];
bool check(int x,int y)
{
    return x>=0&&x<m&&y>=0&&y<n&&!vis[x*n+y]&&maze[x][y]!='#';
}
int getindex(char c)
{
    if(c>='A'&&c<='Z')
       return (int)(c-'A');
    else
       return (int)(c-'a'+26);
}
void bfs(int s,int v)
{
    for(int i=0;i<m*n;++i)
       dist[v][i]=inf;
    dist[v][s]=0;
    memset(vis,0,sizeof(vis));
    queue<int>q;
    q.push(s);
    int x,y,dx,dy;
    while(!q.empty())
    {
        int p=q.front();q.pop();
        if(vis[p]) continue;
        vis[p]=true;
        x=p/n,y=p%n;
        for(int i=0;i<4;++i)
        {
            dx=x+move[i][0];
            dy=y+move[i][1];
            if(check(dx,dy))
            {
                int tmp=dx*n+dy;
                dist[v][tmp]=dist[v][p]+1;
                q.push(tmp);
            }
        }
    }
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!vis[v])
        {
            vis[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int rcnt)
{
    memset(link,0xff,sizeof(link));
    int ret=0;
    for(int i=0;i<rcnt;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ret++;
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        int pos;
        int rcnt=0,tcnt=0;
        for(int i=0;i<m;++i)
        {
            scanf("%s",maze[i]);
            for(int j=0;j<n;++j)
            {
                pos=i*n+j;
                if(maze[i][j]=='*')
                   Treasure[tcnt++]=pos;
                else if((maze[i][j]>='A'&&maze[i][j]<='Z')||(maze[i][j]>='a'&&maze[i][j]<='z'))
                   rally[rcnt].index=getindex(maze[i][j]),rally[rcnt++].pos=pos;
            }
        }
        sort(rally,rally+rcnt);
        bool flag=true;
        if(rcnt==0||rally[0].index!=0) flag=false;
        bfs(rally[0].pos,rally[0].index);
        for(int i=1;i<rcnt;++i)
        {
            if(rally[i].index!=rally[i-1].index+1)
                flag=false;
            if(!flag) break;
            bfs(rally[i].pos,rally[i].index);
        }
        for(int i=0;i<maxn;++i) G[i].clear();
        for(int i=0;i<rcnt-1;++i)
        {
            if(dist[i][rally[i+1].pos]==inf)
            {
                flag=false;
                break;
            }
            for(int j=0;j<tcnt;++j)
            {
                int v=Treasure[j];
                if(dist[i][v]!=inf&&dist[i+1][v]!=inf&&dist[i][v]+dist[i+1][v]==dist[i][rally[i+1].pos])
                   G[i].push_back(v);
            }
        }
        if(!flag)
        {
            printf("-1\n");
            continue;
        }
        int ans=hungary(rcnt);
        printf("%d\n",ans);
    }
    return 0;
}
