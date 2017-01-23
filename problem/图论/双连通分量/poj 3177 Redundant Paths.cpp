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
const int maxn=5000+10;
const int maxm=10000+10;
struct Edge
{
    int v,next;
    Edge (){};
    Edge(int vv,int nn) {v=vv;next=nn;}
}edges[maxm<<1];
int head[maxn],degree[maxn],nEdge,n,m;
int pre[maxn],id[maxn],dfs_clock,ebc_cnt;
stack<int>S;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k!=(fa^1))
        {
            int v=edges[k].v;
            if(!pre[v])
            {
                int lowv=tarjan(v,k);
                lowu=min(lowu,lowv);
                if(lowv>pre[u])
                {
                    ++ebc_cnt;
                    while(true)
                    {
                        int x=S.top();S.pop();
                        id[x]=ebc_cnt;
                        if(x==v) break;
                    }
                }
            }
            else if(lowu>pre[v])
                lowu=pre[v];
        }
    }
    return lowu;
}
int solve()
{
    memset(pre,0,sizeof(pre));
    memset(id,0,sizeof(id));
    memset(degree,0,sizeof(degree));
    dfs_clock=ebc_cnt=0;
    while(!S.empty()) S.pop();
    tarjan(1,-1);
    if(!S.empty())
    {
        ebc_cnt++;
        while(!S.empty())
        {
            int x=S.top();S.pop();
            id[x]=ebc_cnt;
        }
    }
    if(ebc_cnt==1) return 0;
    int u,v;
    for(u=1;u<=n;++u)
    {
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(id[u]!=id[v])
            {
                degree[id[u]]++;
                degree[id[v]]++;
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=ebc_cnt;++i)
        if(degree[i]==2) cnt++;
    return (cnt+1)/2;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    int ans=solve();
    printf("%d\n",ans);
    return 0;
}
