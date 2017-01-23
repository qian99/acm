int color[maxn];
bool bipartite(int u)
{
    for(int i=0;i<g[u].size();++i)
    {
        int v=g[u][i];
        if(color[u]==color[v]) return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v)) return false;
        }
    }
    return true;
}