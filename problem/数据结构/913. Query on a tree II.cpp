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
const int maxn=10000+10;
const int dep=15;
struct Edge
{
    int v,w;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge,n;
int d[maxn],len[maxn],fa[maxn][dep+1];
bool vis[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void bfs()
{
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    d[1]=0;len[1]=0;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(vis[v]) continue;
            d[v]=d[u]+1;
            len[v]=len[u]+edges[k].w;
            fa[v][0]=u;
            q.push(v);
        }
    }
    for(int i=1;i<=dep;++i)
      for(int j=1;j<=n;++j)
         fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int x,int y)
{
    if(x==y) return x;
    if(d[x]>d[y]) swap(x,y);
    for(int i=dep;i>=0;--i)
      if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x) return x;
    if(d[y]>d[x]) y=fa[y][0];
    for(int i=dep;i>=0;--i)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int searchp(int x,int p)
{
    if(p==0) return x;
    for(int i=dep;i>=0;--i)
       if(d[x]-d[fa[x][i]]<p)
       {
           p-=(d[x]-d[fa[x][i]]);
           x=fa[x][i];
       }
    return fa[x][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    char str[10];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        bfs();
        int x,y,z,anc;
        while(~scanf("%s",str))
        {
            if(str[0]=='D'&&str[1]=='O') break;
            if(str[0]=='D')
            {
                scanf("%d%d",&x,&y);
                anc=lca(x,y);
                ll ans=(ll)len[x]+len[y]-(ll)2*len[anc];
                printf("%I64d\n",ans);
            }
            else
            {
                scanf("%d%d%d",&x,&y,&z);
                anc=lca(x,y);
                int res;
                if(d[x]-d[anc]+1>=z)
                  res=searchp(x,z-1);
                else
                {
                    int tmp=d[y]-d[anc];
                    tmp-=(z-(d[x]-d[anc]+1));
                    res=searchp(y,tmp);
                }
                printf("%d\n",res);
            }
        }
        printf("\n");
    }
    return 0;
}

