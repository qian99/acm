//ÏÈbfsËã³öd[x]ºÍfa[x][0]

int fa[maxn][22],d[maxn];

memset(fa,0,sizeof(fa));
for(int i=1;i<=20;++i)
   for(int j=1;j<=n;++j)
      fa[j][i]=fa[fa[j][i-1]][i-1];
int lca(int x,int y)
{
    if(x==y) return x;
    if(d[x]>d[y]) swap(x,y);
    for(int i=20;i>=0;--i)
      if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x)
       return x;
    if(d[y]>d[x]) y=fa[y][0];
    for(int i=20;i>=0;--i)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}