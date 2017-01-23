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
const int maxn=100000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int d[maxn],mind[maxn],pa[maxn][22];
vector<int>rednode;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(pa,0,sizeof(pa));
    memset(mind,0x3f,sizeof(mind));
    d[1]=0;nEdge=-1;
}
void dfs(int u,int fa)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        pa[v][0]=u;
        d[v]=d[u]+1;
        dfs(v,u);
    }
}
void lca_Init(int n)
{
    for(int i=1;i<=20;++i)
        for(int j=1;j<=n;++j)
            pa[j][i]=pa[pa[j][i-1]][i-1];
}
int Lca(int x,int y)
{
    if(x==y) return x;
    if(d[x]>d[y]) swap(x,y);
    for(int i=20;i>=0;--i)
        if(d[pa[y][i]]>d[x]) y=pa[y][i];
    if(pa[y][0]==x) return x;
    if(d[y]>d[x]) y=pa[y][0];
    for(int i=20;i>=0;--i)
    {
        if(pa[y][i]!=pa[x][i])
        {
            y=pa[y][i];
            x=pa[x][i];
        }
    }
    return pa[x][0];
}
void bfs()
{
    queue<int>q;
    int sz=rednode.size();
    for(int i=0;i<sz;++i)
    {
        int v=rednode[i];
        q.push(v);mind[v]=0;
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(mind[v]>mind[u]+1)
            {
                mind[v]=mind[u]+1;
                q.push(v);
            }
        }
    }
    rednode.clear();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,u,v;
    scanf("%d%d",&n,&m);
    Init();
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    dfs(1,-1);
    lca_Init(n);
    rednode.clear();
    rednode.push_back(1);
    bfs();
    int size=sqrt(m)+1,cnt=0;
    while(m--)
    {
        scanf("%d%d",&u,&v);
        if(u==1)
        {
            rednode.push_back(v);
            cnt++;
            if(cnt==size)
            {
                bfs();
                cnt=0;
            }
        }
        else
        {
            int sz=rednode.size();
            int ans=mind[v];
            for(int i=0;i<sz;++i)
            {
                u=rednode[i];
                int anc=Lca(u,v);
                ans=min(ans,d[u]+d[v]-2*d[anc]);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
