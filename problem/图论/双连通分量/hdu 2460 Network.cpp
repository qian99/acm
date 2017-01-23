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
const int dep=18;
const int maxn=100000+10;
const int maxm=200000+10;
struct Edge
{
    int u,v;
};
vector<int>G[maxn],g[maxn];
vector<Edge>edges;
vector<Edge>brights;
int pre[maxn],ebcno[maxn],dfs_clock,ebc_cnt;
int fa[maxn][dep+1],d[maxn],parents[maxn],id[maxn];
bool vis[maxn];
stack<int>S;
void AddEdges(int u,int v)
{
    edges.push_back((Edge){u,v});
    int tmp=edges.size();
    G[u].push_back(tmp-1);
}
int tarjan(int u,int fa)
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
                int lowv=tarjan(v,b);
                lowu=min(lowu,lowv);
                if(lowv>pre[u])
                {
                    brights.push_back((Edge){u,v});
                    ebc_cnt++;
                    while(true)
                    {
                        int x=S.top();S.pop();
                        ebcno[x]=ebc_cnt;
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
    while(!S.empty()) S.pop();
    dfs_clock=ebc_cnt=0;
    tarjan(1,-1);
    if(!S.empty())
    {
        ebc_cnt++;
        while(!S.empty())
        {
            int x=S.top();S.pop();
            ebcno[x]=ebc_cnt;
        }
    }
}
void bfs(int s)
{
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=ebc_cnt;++i) id[i]=i;
    parents[s]=0;
    queue<int>q;
    d[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<g[u].size();++i)
        {
            int v=g[u][i];
            if(!vis[v])
            {
                d[v]=d[u]+1;
                parents[v]=fa[v][0]=u;
                q.push(v);
            }
        }
    }
    for(int i=1;i<=dep;++i)
      for(int j=1;j<=ebc_cnt;++j)
         fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int x,int y)
{
    if(d[x]>d[y]) swap(x,y);
    for(int i=dep;i>=0;--i)
       if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x) return x;
    if(d[y]>d[x]) y=fa[y][0];
    for(int i=dep;i>=0;--i)
    {
        if(fa[y][i]!=fa[x][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
void slove()
{
    find_ebc();
    for(int i=0;i<=ebc_cnt;++i) g[i].clear();
    Edge e;
    for(int i=0;i<brights.size();++i)
    {
        e=brights[i];
        g[ebcno[e.u]].push_back(ebcno[e.v]);
        g[ebcno[e.v]].push_back(ebcno[e.u]);
    }
    bfs(ebcno[1]);
    int q,a,b,total=ebc_cnt-1;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&a,&b);
        int x=ebcno[a],y=ebcno[b];
        if(ebcno[a]==ebcno[b]||id[x]==id[y])
        {
            printf("%d\n",total);
            continue;
        }
        int anc=lca(x,y);
        int tmp;
        x=id[x],y=id[y];
        anc=id[anc];
        while(x!=anc)
        {
            total--;
            tmp=parents[id[x]];
            parents[x]=parents[anc];
            id[x]=anc;
            x=id[tmp];
        }
        while(y!=anc)
        {
            total--;
            tmp=parents[id[y]];
            parents[id[y]]=parents[anc];
            id[y]=anc;
            y=id[tmp];
        }
        printf("%d\n",total);
    }
    printf("\n");
}
int main()
{
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        tcase++;
        for(int i=0;i<=n;++i) G[i].clear();
        edges.clear();
        brights.clear();
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            AddEdges(a,b);
            AddEdges(b,a);
        }
        printf("Case %d:\n",tcase);
        slove();
    }
    return 0;
}
