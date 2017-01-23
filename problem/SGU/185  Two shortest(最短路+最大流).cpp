#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=400+10;
int a[maxn][maxn],d[maxn],n,m;
int cap[maxn][maxn],flow[maxn][maxn];
int pre[maxn],f[maxn],paths[maxn];
bool vis[maxn],inq[maxn];
void spfa()
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[1]=0;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int v=1;v<=n;++v)
        {
            if(a[u][v]!=inf&&d[v]>d[u]+a[u][v])
            {
                d[v]=d[u]+a[u][v];
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
}
void build()
{
    memset(cap,0,sizeof(cap));
    memset(flow,0,sizeof(flow));
    for(int u=1;u<=n;++u)
    {
        for(int v=1;v<=n;++v)
        {
            if(u==v) continue;
            if(a[u][v]!=inf&&d[v]==d[u]+a[u][v])
              cap[u][v]=1;
        }
    }
}
bool bfs()
{
    memset(vis,0,sizeof(vis));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(1);
    pre[1]=0;f[1]=inf;
    vis[1]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int v=1;v<=n;++v)
        {
            if(u==v) continue;
            if(!vis[v]&&a[u][v]!=inf&&cap[u][v]>flow[u][v])
            {
                vis[v]=true;
                pre[v]=u;
                f[v]=min(cap[u][v]-flow[u][v],f[u]);
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    return vis[n];
}
int Maxflow()
{
    int rnt=0;
    while(bfs())
    {
        int u=n;
        while(u!=1)
        {
            int v=pre[u];
            flow[v][u]+=f[u];
            flow[u][v]-=f[u];
            u=v;
        }
        rnt+=f[n];
    }
    return rnt;
}
void findpath()
{
    printf("1");
    int now=1;
    while(now!=n)
    {
        for(int i=1;i<=n;++i)
        {
            if(i==now) continue;
            if(flow[now][i]==1)
            {
                printf(" %d",i);
                flow[now][i]=0;
                now=i;
                break;
            }
        }
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    memset(a,0x3f,sizeof(a));
    for(int i=1;i<=n;++i) a[i][i]=0;
    int u,v,w;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        a[u][v]=a[v][u]=w;
    }
    spfa();
    build();
    int ans=Maxflow();
    if(ans<2) printf("No solution\n");
    else
    {
        findpath();
        findpath();
    }
    return 0;
}
