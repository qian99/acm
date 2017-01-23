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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50;
const int maxm=maxn*maxn;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nx) {v=vv;next=nx;}
}edges[maxm<<3];
const int dir[4][2]={{1,0},{0,1},{0,-1},{-1,0}};
int board[maxn][maxn],head[maxm],nEdge;
int conv[maxm][2];
bool vis[maxm];
int links[maxm];
vector<int>hor,ver;
void AddEdge(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(board,0,sizeof(board));
    memset(head,0xff,sizeof(head));
    memset(links,0xff,sizeof(links));
    nEdge=-1;
    hor.clear();
    ver.clear();
}
bool dfs(int u)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!vis[v])
        {
            vis[v]=true;
            if(links[v]==-1||dfs(links[v]))
            {
                links[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(board[i][j]==0)
            {
                memset(vis,0,sizeof(vis));
                if(dfs((i-1)*n+j)) ans++;
            }
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,p;
    scanf("%d%d",&n,&p);
    Init();
    int x,y,sum=0;
    for(int i=0;i<p;++i)
    {
        scanf("%d%d",&x,&y);
        board[x][y]=-1;
    }
    x=0;y=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            x^=1;
            if(board[i][j]!=-1)
                {board[i][j]=x;sum++;}
            conv[++y][0]=i;conv[y][1]=j;
        }
        x^=1;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(board[i][j]!=0) continue;
            for(int k=0;k<4;++k)
            {
                x=i+dir[k][0];
                y=j+dir[k][1];
                if(x>=1&&x<=n&&y>=1&&y<=n&&board[x][y]!=-1)
                {
                    AddEdge((i-1)*n+j,(x-1)*n+y);
                }
            }
        }
    }
    int ans=hungary(n);
    if((sum&1)||(ans!=sum/2))
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
        for(int i=1;i<=n*n;++i)
        {
            if(links[i]!=-1)
            {
                x=i;
                y=links[i];
                if(x>y) swap(x,y);
                if(conv[x][1]==conv[y][1])
                    hor.push_back(x);
                else
                    ver.push_back(x);
            }
        }
        int size=hor.size();
        printf("%d\n",size);
        for(int i=0;i<size;++i)
            printf("%d %d\n",conv[hor[i]][0],conv[hor[i]][1]);
        size=ver.size();
        printf("%d\n",size);
        for(int i=0;i<size;++i)
            printf("%d %d\n",conv[ver[i]][0],conv[ver[i]][1]);
    }
    return 0;
}

