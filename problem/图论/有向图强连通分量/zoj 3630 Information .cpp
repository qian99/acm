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
const int maxn=100+10;
const int maxm=10000+10;
vector<int>scc[maxn];
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],pre[maxn],sccno[maxn];
int sccid[maxn],dfs_clock,nEdge,scc_cnt,n,m;
bool flag[maxn];
stack<int>S;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    nEdge=-1;dfs_clock=0;scc_cnt=0;
    for(int i=0;i<maxn;++i) scc[i].clear();
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
            lowu=min(lowv,lowu);
        }
        else if(!sccno[v])
            lowu=min(lowu,pre[v]);
    }
    if(pre[u]==lowu)
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
int dfs(int u,int x,int id,int &tot)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==x||sccno[v]!=id) continue;
        if(!pre[v])
        {
            int lowv=dfs(v,x,id,tot);
            lowu=min(lowv,lowu);
        }
        else if(!sccid[v])
            lowu=min(lowu,pre[v]);
    }
    if(pre[u]==lowu)
    {
        scc_cnt++;
        int tmp=0;
        while(true)
        {
            int x=S.top();S.pop();
            if(sccid[x]!=scc_cnt) tmp++;
            sccid[x]=scc_cnt;
            if(x==u) break;
        }
        tot=max(tot,tmp);
    }
    return lowu;
}
int solve()
{
    for(int i=1;i<=n;++i)
        if(!pre[i]) tarjan(i);
    int maxp=-inf,maxp2=-inf,size;
    for(int i=1;i<=n;++i)
        scc[sccno[i]].push_back(i);
    int pos=-1;
    for(int i=1;i<=scc_cnt;++i)
    {
        size=scc[i].size();
        if(size>maxp)
        {
            maxp2=maxp;
            maxp=size;
            pos=i;
        }
        else if(size>maxp2)
            maxp2=size;
    }
    size=scc[pos].size();
    int u,minv=maxp,tot,x;
    for(int i=0;i<size;++i)
    {
        tot=0;
        memset(pre,0,sizeof(pre));
        memset(sccid,0,sizeof(sccid));
        dfs_clock=0;scc_cnt=0;
        x=scc[pos][i];
        for(int j=0;j<size;++j)
        {
            if(i==j) continue;
            u=scc[pos][j];
            if(!pre[u])
                dfs(u,x,pos,tot);
        }
        minv=min(minv,max(tot,maxp2));
    }
    return minv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(++u,++v);
        }
        int ans=solve();
        if(ans==1) ans=0;
        printf("%d\n",ans);
    }
    return 0;
}
