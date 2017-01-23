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
const int maxn=10000+10;
const int maxq=1000000+10;
struct Edge
{
    int v;
    int w;
    int next;
};
struct Node
{
    int v;
    int num;
};
Edge edges[maxn<<1];
int head[maxn],nEdge,n,m,c,cnt;
int color[maxn],parents[maxn];
int res[maxq];
vector<Node>qes[maxn];
bool vis[maxn];
int len[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    x=Find(x);y=Find(y);
    if(x!=y)
      parents[y]=x;
}
void tarjan(int u)
{
    color[u]=cnt;
    vis[u]=true;
    parents[u]=u;
    int sz=qes[u].size();
    Node tmp;
    for(int i=0;i<sz;++i)
    {
        tmp=qes[u][i];
        if(vis[tmp.v]&&color[u]==color[tmp.v])
           res[tmp.num]=len[u]+len[tmp.v]-2*len[Find(tmp.v)];
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!vis[v])
        {
            len[v]=len[u]+edges[k].w;
            tarjan(v);
            parents[v]=u;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&c))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        for(int i=0;i<=n;++i)
        {
            qes[i].clear();
            parents[i]=i;
            len[i]=0;
        }
        Node tmp;
        for(int i=0;i<c;++i)
        {
            res[i]=-1;
            scanf("%d%d",&u,&v);
            tmp.v=v;tmp.num=i;
            qes[u].push_back(tmp);
            tmp.v=u;
            qes[v].push_back(tmp);
        }
        memset(vis,0,sizeof(vis));
        memset(color,0,sizeof(color));
        cnt=0;
        for(int i=1;i<=n;++i)
           if(!vis[i]) cnt++,tarjan(i);
        for(int i=0;i<c;++i)
        {
            if(res[i]==-1)
              puts("Not connected");
            else printf("%d\n",res[i]);
        }
    }
    return 0;
}
