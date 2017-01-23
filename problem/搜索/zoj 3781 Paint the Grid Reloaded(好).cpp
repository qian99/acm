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
const int maxn=55;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn*maxn*20];
int head[maxn*maxn],d[maxn*maxn],nEdge,n,m;
char mat[maxn][maxn];
int id[maxn][maxn],icnt;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
void dfs(int x,int y)
{
    id[x][y]=icnt;
    int dx,dy;
    for(int i=0;i<4;++i)
    {
        dx=x+dirx[i];
        dy=y+diry[i];
        if(check(dx,dy)&&!id[dx][dy]&&mat[dx][dy]==mat[x][y])
            dfs(dx,dy);
    }
}
int bfs(int s)
{
    queue<int>q;
    memset(d,0xff,sizeof(d));
    q.push(s);
    d[s]=0;
    int maxv=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]==-1)
            {
                d[v]=d[u]+1;
                q.push(v);
                maxv=max(maxv,d[v]);
            }
        }
    }
    return maxv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i)
            scanf("%s",mat[i]);
        memset(id,0,sizeof(id));
        icnt=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(!id[i][j])
                {
                    ++icnt;
                    dfs(i,j);
                }
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int dx,dy;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                for(int k=0;k<4;++k)
                {
                    dx=i+dirx[k];
                    dy=j+diry[k];
                    if(check(dx,dy)&&id[i][j]!=id[dx][dy])
                        AddEdges(id[i][j],id[dx][dy]);
                }
        int ans=inf;
        for(int i=1;i<=icnt;++i)
            ans=min(ans,bfs(i));
        printf("%d\n",ans);
    }
    return 0;
}

