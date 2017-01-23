#include <iostream>
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
const int maxm=20000+10;
struct Edge
{
    int u,v;
};
int n,m,total,minvalue;
int value[maxn],sum[maxn];
int pre[maxn],id[maxn],dfs_clock,ebc_cnt;
stack<int>S;
bool vis[maxn];
vector<int>G[maxn];
vector<int>g[maxn];
vector<Edge>edges;
void AddEdges(int u,int v)
{
    edges.push_back((Edge){u,v});
    int temp=edges.size();
    G[u].push_back(temp-1);
}
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    int b;
    for(int i=0;i<G[u].size();++i)
    {
        b=G[u][i];
        if(b!=(fa^1))
        {
            int v=edges[b].v;
            if(!pre[v])
            {
                int lowv=dfs(v,b);
                lowu=min(lowu,lowv);
                if(lowv>pre[u])
                {
                    ebc_cnt++;
                    while(true)
                    {
                        int x=S.top();S.pop();
                        id[x]=ebc_cnt;
                        if(x==v) break;
                    }

                }
            }
            else if(pre[v]<lowu)
                   lowu=pre[v];
        }
    }
    return lowu;
}
void find_ebc()
{
    memset(pre,0,sizeof(pre));
    memset(id,0,sizeof(id));
    while(!S.empty()) S.pop();
    dfs_clock=0;ebc_cnt=0;
    dfs(0,-1);
    if(!S.empty())
    {
        ebc_cnt++;
        while(!S.empty())
        {
            int x=S.top();S.pop();
            id[x]=ebc_cnt;
        }
    }
}
int ff(int u)
{
    vis[u]=true;
    int a=0;
    for(int i=0;i<g[u].size();++i)
    {
        int v=g[u][i];
        if(!vis[v])
        {
            int temp=ff(v);
            minvalue=min(minvalue,abs(total-2*temp));
            a+=temp;
        }
    }
    return a+sum[u];
}
int slove()
{
    find_ebc();
    if(ebc_cnt==1) return -1;
    memset(sum,0,sizeof(sum));
    total=0;
    for(int i=0;i<n;++i)
    {
        sum[id[i]]+=value[i];
        total+=value[i];
        g[i].clear();
    }
    for(int i=0;i<=ebc_cnt;++i) g[i].clear();
    for(int i=0;i<edges.size();++i)
    {
        Edge e=edges[i];
        if(id[e.u]!=id[e.v])
           g[id[e.u]].push_back(id[e.v]);
    }
    minvalue=0x7fffffff;
    memset(vis,0,sizeof(vis));
    ff(1);
    return minvalue;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        edges.clear();
        for(int i=0;i<n;++i)
        {
            scanf("%d",&value[i]);
            G[i].clear();
        }
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            AddEdges(a,b);
            AddEdges(b,a);
        }
        int ans=slove();
        if(ans==-1) printf("impossible\n");
        else printf("%d\n",ans);
    }
    return 0;
}

