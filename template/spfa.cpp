int spfa(int s,int t)
{
    for(int i=0;i<=n;++i) d[i]=inf;
    memset(inq,0,sizeof(inq));
    d[s]=0;inq[s]=true;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    return d[t]==inf?-1:d[t];
}