#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=300000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
int pa[maxn];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
int minv[maxn][2],sons[maxn][2],dp[maxn][2],mxlen,mxv,resu;
bool vis[maxn];
int S[maxn],tot;
void dfs(int u,int fa)
{
    vis[u]=true;
    S[tot++]=u;
    minv[u][0]=minv[u][1]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        if(minv[v][0]+1>minv[u][0])
        {
            minv[u][1]=minv[u][0];
            minv[u][0]=minv[v][0]+1;
            sons[u][1]=sons[u][0];
            sons[u][0]=v;
        }
        else if(minv[v][0]+1>minv[u][1])
        {
            minv[u][1]=minv[v][0]+1;
            sons[u][1]=v;
        }
    }
}
void dfs2(int u,int fa,int ml)
{
    if(minv[u][0]+minv[u][1]>mxlen)
    {
        mxlen=minv[u][0]+minv[u][1];
        mxv=max(minv[u][0],minv[u][1]);
        dp[u][0]=minv[u][0];
        dp[u][1]=minv[u][1];
        resu=u;
    }
    else if(minv[u][0]+minv[u][1]==mxlen)
    {
        int tmp=max(minv[u][0],minv[u][1]);
        if(tmp<mxv)
        {
            dp[u][0]=minv[u][0];
            dp[u][1]=minv[u][1];
            mxv=tmp;
            resu=u;
        }
    }
    if(minv[u][0]+ml>mxlen)
    {
        mxlen=minv[u][0]+ml;
        mxv=max(minv[u][0],ml);
        resu=u;
        dp[u][0]=minv[u][0];
        dp[u][1]=ml;
        if(dp[u][0]<dp[u][1]) swap(dp[u][0],dp[u][1]);
    }
    else if(minv[u][0]+ml==mxlen)
    {
        int tmp=max(minv[u][0],ml);
        if(tmp<mxv)
        {
            mxv=tmp;
            resu=u;
            dp[u][0]=minv[u][0];
            dp[u][1]=ml;
            if(dp[u][0]<dp[u][1]) swap(dp[u][0],dp[u][1]);
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(sons[u][0]==v) dfs2(v,u,max(ml,minv[u][1])+1);
        else dfs2(v,u,max(ml,minv[u][0])+1);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w ",stdout);
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        AddEdges(u,v);
    }
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)
    {
        if(!vis[i])
        {
            tot=0;
            mxlen=-1;
            mxv=inf;
            dfs(i,-1);
            dfs2(i,-1,0);
            for(int j=0;j<tot;++j)
            {
                pa[S[j]]=resu;
            }
        }
    }
    int type,x,y;
    while(q--)
    {
        scanf("%d%d",&type,&x);
        if(type == 1)
        {
            x=Find(x);
            printf("%d\n",dp[x][0]+dp[x][1]);
        }
        else
        {
            scanf("%d",&y);
            u=Find(x);
            v=Find(y);
            if(u==v) continue;
            if((dp[u][0]+dp[u][1]>dp[v][0]+dp[u][0]+1)||(dp[v][0]+dp[v][1]>dp[v][0]+dp[u][0]+1))
            {
                if(dp[u][0]+dp[u][1]>dp[v][0]+dp[v][1])
                    pa[v]=u;
                else pa[u]=v;
            }
            else if(dp[u][0]+1>dp[v][0]+1)
            {
                dp[u][1]=max(dp[u][1],dp[v][0]+1);
                if(dp[u][1]>dp[u][0]) swap(dp[u][1],dp[u][0]);
                pa[v]=u;
            }
            else
            {
                dp[v][1]=max(dp[v][1],dp[u][0]+1);
                if(dp[v][1]>dp[v][0]) swap(dp[v][1],dp[v][0]);
                pa[u]=v;
            }
        }
    }
    return 0;
}
