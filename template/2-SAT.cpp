//“ª∞„Õº∆•≈‰À„∑®
bool g[maxn][maxn],inque[maxn],inblossom[maxn],inpath[maxn];
int match[maxn],pre[maxn],fa[maxn];
queue<int>q;
int lca(int u,int v)
{
    memset(inpath,0,sizeof(inpath));
    while(true)
    {
        u=fa[u];
        inpath[u]=true;
        if(match[u]==-1) break;
        u=pre[match[u]];
    }
    while(true)
    {
        v=fa[v];
        if(inpath[v]) return v;
        v=pre[match[v]];
    }
}
void reset(int u,int anc)
{
    while(u!=anc)
    {
        int v=match[u];
        inblossom[fa[u]]=inblossom[fa[v]]=1;
        v=pre[v];
        if(fa[v]!=anc) pre[v]=match[u];
        u=v;
    }
}
void contract(int u,int v,int n)
{
    int anc=lca(u,v);
    memset(inblossom,0,sizeof(inblossom));
    reset(u,anc);reset(v,anc);
    if(fa[u]!=anc)pre[u]=v;
    if(fa[v]!=anc)pre[v]=u;
    for(int i=1;i<=n;i++)
        if(inblossom[fa[i]])
        {
            fa[i]=anc;
            if(!inque[i])
            {
                q.push(i);
                inque[i]=1;
            }
        }
}
bool bfs(int S,int n)
{
    for(int i=0;i<=n;i++)pre[i]=-1,inque[i]=0,fa[i]=i;
    while(!q.empty()) q.pop();
    q.push(S);inque[S]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int v=1;v<=n;v++)
        {
            if(g[u][v]&&fa[v]!=fa[u]&&match[u]!=v)
            {
                if(v==S||(match[v]!=-1&&pre[match[v]]!=-1))contract(u,v,n);
                else if(pre[v]==-1)
                {
                    pre[v]=u;
                    if(match[v]!=-1)q.push(match[v]),inque[match[v]]=1;
                    else
                    {
                        u=v;
                        while(u!=-1)
                        {
                            v=pre[u];
                            int w=match[v];
                            match[u]=v;
                            match[v]=u;
                            u=w;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int solve(int n)
{
    memset(match,0xff,sizeof(match));
    int ans=0;
    for(int i=1;i<=n;i++)
        if(match[i]==-1&&bfs(i,n))
            ans++;
    return ans;
}