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
using namespace std;
const int maxn=500+10;
const int maxm=maxn*maxn;
struct Edge
{
    int v,w,next;
};
Edge edges[maxm],ee[maxm];
int head[maxn],hh[maxn];
int pre[maxn],sccno[maxn],d[maxn],ways[maxn][maxn];
int dfs_clock,scc_cnt,n,m,nEdge,ecnt;
bool inq[maxn],flag[maxn];
stack<int>S;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void addedge(int u,int v,int w)
{
    ecnt++;
    ee[ecnt].v=v;
    ee[ecnt].w=w;
    ee[ecnt].next=hh[u];
    hh[u]=ecnt;
}
void Init()
{
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(head,0xff,sizeof(head));
    memset(hh,0xff,sizeof(hh));
    memset(flag,0,sizeof(flag));
    nEdge=ecnt=-1;
    dfs_clock=scc_cnt=0;
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
void spfa(int s)
{
    memset(inq,0,sizeof(inq));
    for(int i=1;i<=scc_cnt;++i) d[i]=inf;
    d[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=hh[u];k!=-1;k=ee[k].next)
        {
            int v=ee[k].v;
            if(d[v]>d[u]+ee[k].w)
            {
                d[v]=d[u]+ee[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    for(int i=1;i<=scc_cnt;++i)
      ways[s][i]=d[i];
}
void solve()
{
    for(int i=1;i<=n;++i)
      if(!pre[i]) tarjan(i);
    for(int i=1;i<=scc_cnt;++i)
    {
        ways[i][i]=0;
        for(int j=i+1;j<=scc_cnt;++j)
         ways[i][j]=ways[j][i]=inf;
    }
    int u,v;
    for(u=1;u<=n;++u)
    {
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(sccno[u]!=sccno[v])
             addedge(sccno[u],sccno[v],edges[k].w);
        }
    }
    int q;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&u,&v);
        if(sccno[u]==sccno[v])
        {
            printf("0\n");
            continue;
        }
        if(!flag[sccno[u]])
          spfa(sccno[u]);
        flag[sccno[u]]=true;
        if(ways[sccno[u]][sccno[v]]==inf)
          printf("Nao e possivel entregar a carta\n");
        else
          printf("%d\n",ways[sccno[u]][sccno[v]]);
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0) break;
        Init();
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        solve();
    }
    return 0;
}
