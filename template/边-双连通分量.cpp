vector<int>G[maxn];
stack<int>S;
int pre[maxn],id[maxn],dfs_clock,ebc_cnt;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            lowu=min(lowu,pre[v]);
        }
    }
    if(lowu==pre[u])
    {
        ebc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            id[x]=ebc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_ebc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(id,0,sizeof(id));
    while(!S.empty()) S.pop();
    dfs_clock=ebc_cnt=0;
    for(int i=1;i<=n;++i)
      if(!pre[i]) dfs(i,-1);
}






//有重边的情况

const int maxn=10000+10;
const int maxm=20000+10;
struct Edge
{
    int u,v;
};
int n,m;
int pre[maxn],id[maxn],dfs_clock,ebc_cnt;
stack<int>S;
bool vis[maxn];
vector<int>G[maxn];
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