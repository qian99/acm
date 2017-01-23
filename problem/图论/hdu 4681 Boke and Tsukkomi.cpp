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
const int maxn=50;
const int maxm=200;
bool g[maxn][maxn],inque[maxn],inblossom[maxn],inpath[maxn];
int match[maxn],pre[maxn],fa[maxn];
queue<int>q;
pair<int,int>edges[maxm];
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
bool isans[maxn][maxn];
int res[maxm];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(isans,0,sizeof(isans));
        memset(g,0,sizeof(g));
        int a,b;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&a,&b);
            edges[i]=make_pair(a,b);
            g[a][b]=g[b][a]=true;
        }
        int r=solve(n),u,v,ux,vx,p=0;
        for(int i=1;i<=m;++i)
        {
            memset(g,0,sizeof(g));
            ux=edges[i].first;
            vx=edges[i].second;
            for(int j=1;j<=m;++j)
            {
                if(i!=j)
                {
                    u=edges[j].first;
                    v=edges[j].second;
                    if(u==ux||u==vx||v==ux||v==vx) continue;
                    g[u][v]=g[v][u]=true;
                }
            }
            if(r-1!=solve(n)) res[p++]=i;
        }
        sort(res,res+p);
        printf("%d\n",p);
        if(p>0) printf("%d",res[0]);
        for(int i=1;i<p;++i)
           printf(" %d",res[i]);
        printf("\n");
    }
    return 0;
}
