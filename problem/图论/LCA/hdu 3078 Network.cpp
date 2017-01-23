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
const int maxn=80000+10;
const int dep=17;
struct Edge
{
    int v;
    int next;
};
int w[maxn],fa[maxn][dep+1],d[maxn],n,q,nEdge;
int head[maxn];
int num[maxn];
Edge edges[maxn<<1];
void AddEdges(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int f)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==f) continue;
        d[v]=d[u]+1;
        dfs(v,u);
        fa[v][0]=u;
    }
}
void getfa()
{
    d[0]=0;
    memset(fa,0,sizeof(fa));
    dfs(1,-1);
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
        if(fa[y][i]!=fa[x][i])
        {
            y=fa[y][i];
            x=fa[x][i];
        }
    }
    return fa[x][0];
}
int solve(int x,int a,int b)
{
    int cnt=0;
    int anc=lca(a,b);
    while(a!=anc)
    {
        num[++cnt]=w[a];
        a=fa[a][0];
    }
    while(b!=anc)
    {
        num[++cnt]=w[b];
        b=fa[b][0];
    }
    num[++cnt]=w[anc];
    if(cnt<x) return -1;
    sort(num+1,num+cnt+1);
    return num[cnt-x+1];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&q))
    {
        for(int i=1;i<=n;++i)
          scanf("%d",&w[i]);
        int a,b,c;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&a,&b);
            AddEdges(a,b);
            AddEdges(b,a);
        }
        getfa();
        while(q--)
        {
            scanf("%d%d%d",&c,&a,&b);
            if(c==0)
              w[a]=b;
            else
            {
                int ans=solve(c,a,b);
                if(ans==-1) printf("invalid request!\n");
                else printf("%d\n",ans);
            }
        }
    }
    return 0;
}
