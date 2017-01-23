//复杂度：邻接矩阵O(n^3)   邻接表O(mn)

vector<int>G[maxn];
bool used[maxn];
int link[maxn];
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i)) res++;
    }
    return res;
}