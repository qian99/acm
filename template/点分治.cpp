int head[maxn],q[maxn],flag[maxn],dp[maxn],fa[maxn];
int getroot(int x)
{
    int tail = 0,u,v,root,minv = inf;
    q[tail++] = x; fa[x] = -1;
    for(int i = 0;i < tail;++i)
    {
        u = q[i];
        dp[u] = 1;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v != fa[u] && !flag[v])
            {
                q[tail++] = edges[k].v;
                fa[v] = u;
            }
        }
    }
    for(int i = tail - 1;i >= 0;--i)
    {
        u = q[i];
        int mx = 0;
        for(int k = head[u];k != -1;k = edges[k].next)
        {
            v = edges[k].v;
            if(v != fa[u] && !flag[v])
            {
                if(dp[v] > mx) mx = dp[v];
                dp[u] += dp[v];
            }
        }
        mx = max(mx,tail - dp[u]);
        if(mx < minv) minv = mx,root = u;
    }
    return root;
}
void solve(int u)
{
    int root = getroot(u);
    flag[root] = 1;
    for(int k = head[root];k != -1; k = edges[k].next)
        if(!flag[edges[k].v])
            //do someting to cal
    for(int k = head[root];k != -1; k = edges[k].next)
        if(!flag[edges[k].v]) solve(edges[k].v);
}