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
const int maxn=100000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],d[maxn],val[maxn],goal[maxn],nEdge;
int ans[maxn],tot;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa,int x,int y)
{
    if(d[u]&1)
    {
        val[u]^=x;
        if(val[u]!=goal[u]) {x^=1;ans[tot++]=u;}
    }
    else
    {
        val[u]^=y;
        if(val[u]!=goal[u]) {y^=1;ans[tot++]=u;}
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue ;
        d[v]=d[u]+1;
        dfs(v,u,x,y);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int u,v;
    scanf("%d",&n);
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    for(int i=1;i<=n;++i)
        scanf("%d",&val[i]);
    for(int j=1;j<=n;++j)
        scanf("%d",&goal[j]);
    tot=0;
    d[1]=0;
    dfs(1,-1,0,0);
    printf("%d\n",tot);
    for(int i=0;i<tot;++i)
        printf("%d\n",ans[i]);
    return 0;
}