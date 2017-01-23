int w[maxn][maxn];
int lx[maxn],ly[maxn],link[maxn],slack[maxn];
bool S[maxn],T[maxn];
int n;
bool match(int u)
{
    S[u]=true;
    for(int i=1;i<=n;++i)
    {
        if(!T[i])
        {
            if(lx[u]+ly[i]==w[u][i])
            {
                T[i]=true;
                if(!link[i]||match(link[i]))
                {
                    link[i]=u;
                    return true;
                }
            }
            else
                slack[i]=min(slack[i],lx[u]+ly[i]-w[u][i]);
        }
    }
    return false;
}
void update()
{
    int d=inf;
    for(int i=1;i<=n;++i) if(!T[i])
      d=min(d,slack[i]);
    for(int i=1;i<=n;++i)
    {
        if(S[i]) lx[i]-=d;
        if(T[i]) ly[i]+=d;
    }
}
void KM()
{
    for(int i=1;i<=n;++i)
    {
        link[i]=lx[i]=ly[i]=0;
        for(int j=1;j<=n;++j)
          lx[i]=max(lx[i],w[i][j]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) slack[j]=inf;
        for(;;)
        {
            for(int k=1;k<=n;++k) S[k]=T[k]=0;
            if(match(i)) break;
            else update();
        }
    }
}