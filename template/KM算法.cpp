int w[maxn][maxn],g[maxn][maxn],n,m;
int lx[maxn],ly[maxn],links[maxn],slack;
bool S[maxn],T[maxn];
bool dfs(int u)
{
    S[u]=true;
    int tmp,v;
    for(int i=1;i<=g[u][0];++i)
    {
        v=g[u][i];
        if(!w[u][v]) continue;
        tmp=lx[u]+ly[v]-w[u][v];
        if(tmp==0)
        {
            if(!T[v])
            {
                T[v]=true;
                if(!links[v]||dfs(links[v]))
                {
                    links[v]=u;
                    return true;
                }
            }
        }
        else slack=min(slack,tmp);
    }
    return false;
}
void update()
{
    for(int i=1;i<=n;++i)
    {
        if(S[i]) lx[i]-=slack;
        if(T[i]) ly[i]+=slack;
    }
}
void KM()
{
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(links,0,sizeof(links));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            lx[i]=max(lx[i],w[i][j]);
    for(int i=1;i<=n;++i)
    {
        slack=inf;
        while(true)
        {
            memset(S,0,sizeof(S));
            memset(T,0,sizeof(T));
            if(dfs(i)) break;
            else update();
        }
    }
}