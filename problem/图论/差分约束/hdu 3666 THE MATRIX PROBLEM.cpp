#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
const int maxm=200000+10;
struct Edge
{
    int v,next;
    double w;
};
Edge edges[maxm<<1];
int head[maxn],nEdge;
double d[maxn];
bool ins[maxn],vis[maxn];
void AddEdge(int u,int v,double w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
bool spfa(int u)
{
    if(ins[u]) return false;
    ins[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(d[v]>d[u]+edges[k].w)
        {
            d[v]=d[u]+edges[k].w;
            if(!spfa(v)) return false;
        }
    }
    ins[u]=false;
    return true;
}
bool check(int n)
{
    for(int i=0;i<=n;++i)
      vis[i]=ins[i]=d[i]=0;
    for(int i=0;i<=n;++i)
      if(!vis[i])
        if(!spfa(i))
          return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,l,r;
    while(~scanf("%d%d%d%d",&n,&m,&l,&r))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int tmp;
        for(int i=1;i<=n;++i)
          for(int j=1;j<=m;++j)
          {
              scanf("%d",&tmp);
              AddEdge(j+n,i,log((double)r/tmp));
              AddEdge(i,j+n,-log((double)l/tmp));
          }
        int N=n+m;
        for(int i=1;i<=N;++i)
          AddEdge(0,i,0);
        if(check(N))
          printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
