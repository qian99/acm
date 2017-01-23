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
const int maxn=100000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int cnt[maxn],tar[maxn],path[maxn<<2],tot;
bool vis[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u)
{
    cnt[u]^=1;
    path[tot++]=u;
    vis[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(vis[v]) continue;
        dfs(v);
        path[tot++]=u;
        cnt[u]^=1;
        if(cnt[v]!=tar[v])
        {
            path[tot++]=v;
            path[tot++]=u;
            cnt[v]^=1;
            cnt[u]^=1;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    int u,v;
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    int s=1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&tar[i]);
        if(tar[i]) s=i;
    }
    dfs(s);
    if(cnt[s]!=tar[s]) tot--;
    bool flag=true;
    for(int i=1;i<=n;++i)
        if(!vis[i]&&tar[i]) flag=false;
    if(!flag) printf("-1\n");
    else
    {
        printf("%d\n",tot);
        for(int i=0;i<tot;++i)
        {
            if(i) printf(" ");
            printf("%d",path[i]);
        }
        printf("\n");
    }
    return 0;
}

