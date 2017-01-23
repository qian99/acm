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
const int maxn=1000+10;
const int maxm=6000+10;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nx){v=vv;next=nx;}
}edges[maxm],ee[maxm];
int head[maxn],hh[maxn],sccno[maxn],pre[maxn],degree[maxn],path[maxn];
bool vis[maxn];
int dfs_clock,nEdge,scc_cnt,ne,maxlen;
stack<int>S;
void AddEdge(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void addedge(int u,int v)
{
    ee[++ne]=Edge(v,hh[u]);
    hh[u]=ne;
}
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowu,lowv);
        }
        else if(!sccno[v])
            lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        scc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    while(!S.empty())S.pop();
}
void dfs(int u,int len)
{
    path[u]=len;
    maxlen=max(maxlen,path[u]);
    for(int k=hh[u];k!=-1;k=ee[k].next)
    {
        int v=ee[k].v;
        if(path[u]>path[v]) dfs(v,len+1);
    }
}
bool check(int n)
{
    if(scc_cnt==1) return true;
    memset(degree,0,sizeof(degree));
    memset(hh,0xff,sizeof(hh));
    memset(vis,0,sizeof(vis));
    memset(path,0,sizeof(path));
    ne=-1;
    int u,v;
    for(u=1;u<=n;++u)
    {
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(sccno[u]!=sccno[v])
            {
                addedge(sccno[u],sccno[v]);
                degree[sccno[v]]++;
            }
        }
    }
    maxlen=0;
    for(int i=1;i<=scc_cnt;++i)
        if(degree[i]==0) {dfs(i,1);break;}
    return maxlen==scc_cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        scanf("%d%d",&n,&m);
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        for(int i=1;i<=n;++i)
            if(!pre[i]) tarjan(i);
        if(check(n))
            printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
