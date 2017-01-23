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
const int maxn=50000+10;
struct Edge
{
    int v,next;
    Edge (){};
    Edge(int vv,int nx) {v=vv;next=nx;}
}edges[maxn<<1];
struct Node
{
    int u,v,id;
    Node(){};
    Node(int uu,int vv,int ii){u=uu;v=vv;id=ii;}
};
int head[maxn],val[maxn],ans[maxn],nEdge;
int pa[maxn],maxv[maxn],minv[maxn],bestv[maxn],ups[maxn];
bool vis[maxn];
vector<pair<int,int> >querys[maxn];
vector<Node>noq[maxn];
int Find(int x)
{
    if(x==pa[x]) return x;
    Find(pa[x]);
    int y=pa[x];
    ups[x]=max(ups[x],max(ups[y],maxv[x]-minv[y]));
    bestv[x]=max(bestv[x],max(bestv[y],maxv[y]-minv[x]));
    maxv[x]=max(maxv[y],maxv[x]);
    minv[x]=min(minv[y],minv[x]);
    pa[x]=pa[y];
    return pa[x];
}
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
inline int getbest(int x,int y)
{
    int res=max(bestv[x],ups[y]);
    res=max(maxv[y]-minv[x],res);
    return res;
}
void tarjan(int u,int fa)
{
    pa[u]=u;bestv[u]=ups[u]=0;
    maxv[u]=minv[u]=val[u];
    vis[u]=true;
    int v,size,anc;
    pair<int,int>pp;
    size=querys[u].size();
    bool flag;
    for(int i=0;i<size;++i)
    {
        flag=false;
        pp=querys[u][i];
        v=pp.first;
        if(v<0) {v=-v;flag=true;}
        if(vis[v])
        {
            anc=Find(v);
            if(flag) noq[anc].push_back(Node(u,v,pp.second));
            else noq[anc].push_back(Node(v,u,pp.second));
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].v;
        if(v==fa) continue;
        tarjan(v,u);
        pa[v]=u;
    }
    size=noq[u].size();
    Node node;
    for(int i=0;i<size;++i)
    {
        node=noq[u][i];
        Find(node.u);Find(node.v);
        ans[node.id]=getbest(node.u,node.v);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q,u,v;
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    nEdge=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&val[i]);
        querys[i].clear();
        noq[i].clear();
    }
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    scanf("%d",&q);
    for(int i=0;i<q;++i)
    {
        scanf("%d%d",&u,&v);
        querys[u].push_back(make_pair(-v,i));
        querys[v].push_back(make_pair(u,i));
    }
    tarjan(1,-1);
    for(int i=0;i<q;++i)
        printf("%d\n",ans[i]);
    return 0;
}

