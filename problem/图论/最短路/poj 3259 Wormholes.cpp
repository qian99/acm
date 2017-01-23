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
const int maxn=500+10;
const int maxm=3000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],n,m,wnt;
bool inq[maxn],vis[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
bool spfa(int u)
{
    vis[u]=true;
    inq[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(d[v]>d[u]+edges[k].w)
        {
            d[v]=d[u]+edges[k].w;
            if(!inq[v])
            {
                if(spfa(v)) return true;
            }
            else
              return true;
        }
    }
    inq[u]=false;
    return false;
}
bool solve()
{
    memset(inq,0,sizeof(inq));
    memset(vis,0,sizeof(vis));
    memset(d,0x3f,sizeof(d));
    for(int i=1;i<=n;++i)
      if(!vis[i])
      {
          if(spfa(i)) return true;
      }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&wnt);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        for(int i=0;i<wnt;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,-w);
        }
        if(solve()) puts("YES");
        else puts("NO");
    }
    return 0;
}
