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
const int maxm=50000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxm<<1],ee[maxm<<1];
int head[maxn],hh[maxn],nEdge,ne;
int pre[maxn],sccno[maxn],dfs_clock,scc_cnt;
int degree[maxn],d2[maxn],val[maxn],sup[maxn],maxsup;
stack<int>S;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void addedge(int u,int v)
{
    ne++;
    ee[ne].v=v;
    ee[ne].next=hh[u];
    hh[u]=ne;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(hh,0xff,sizeof(hh));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(degree,0,sizeof(degree));
    memset(sup,0,sizeof(sup));
    memset(val,0,sizeof(val));
    memset(d2,0,sizeof(d2));
    nEdge=ne=-1;
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
void find_scc(int n)
{
    dfs_clock=scc_cnt=0;
    for(int i=1;i<=n;++i)
      if(!pre[i]) tarjan(i);
}
void dfs(int u)
{
    if(val[u]>1) sup[u]+=(val[u]-1);
    maxsup=max(maxsup,sup[u]);
    for(int k=hh[u];k!=-1;k=ee[k].next)
    {
        int v=ee[k].v;
        sup[v]+=sup[u]+1;
        d2[v]++;
        if(d2[v]==degree[v])
        dfs(v);
    }
}
void solve(int n)
{
    int v;
    for(int u=1;u<=n;++u)
    {
        val[sccno[u]]++;
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
    maxsup=0;
    for(int i=1;i<=scc_cnt;++i)
      if(!degree[i]) dfs(i);
    if(maxsup!=n-1)
    {
        printf("0\n");
        return;
    }
    int cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(sup[sccno[i]]==maxsup)
          cnt++;
    }
    printf("%d\n",cnt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    Init();
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdge(u,v);
    }
    find_scc(n);
    solve(n);
    return 0;
}
