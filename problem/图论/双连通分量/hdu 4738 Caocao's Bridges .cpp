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
const int maxn=1000+10;
const int maxm=1000000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge;
int pre[maxn],dfs_clock,cnt,ans;
int n,m;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k!=(fa^1))
        {
            int v=edges[k].v;
            if(!pre[v])
            {
                int lowv=tarjan(v,k);
                lowu=min(lowv,lowu);
                if(lowv>pre[u])
                    ans=min(ans,edges[k].w);
            }
            else if(pre[v]<lowu)
              lowu=pre[v];
        }
    }
    return lowu;
}
void find_ebc()
{
    dfs_clock=cnt=0;
    ans=inf;
    memset(pre,0,sizeof(pre));
    for(int i=1;i<=n;++i)
      if(!pre[i]) tarjan(i,-1),cnt++;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        find_ebc();
        if(cnt>1)
          ans=0;
        else if(ans==0) ans=1;
        if(ans==inf)
          printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
