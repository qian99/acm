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
const int maxn=100+10;
int a[maxn][maxn];
int dis[maxn],n,m,k,S,T,cnt;
int pa[maxn],total;
bool vis[maxn],finds;
void spfa()
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[T]=0;
    queue<int>q;
    q.push(T);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=false;
        for(int i=1;i<=n;++i)
        {
            if(a[u][i]+dis[u]<dis[i])
            {
                dis[i]=a[u][i]+dis[u];
                if(!vis[i]) {q.push(i);vis[i]=true;}
            }
        }
    }
}
void dfs(int u,int len,int val)
{
    if(u==T)
    {
        cnt++;
        if(cnt>=k) finds=true;
        return ;
    }
    if(len+dis[u]>val) return ;
    for(int v=1;v<=n;++v)
    {
        if(!vis[v]&&len+a[u][v]<=val)
        {
            vis[v]=true;
            dfs(v,len+a[u][v],val);
            vis[v]=false;
            if(finds) return ;
        }
    }
}
bool test(int val)
{
    memset(vis,0,sizeof(vis));
    cnt=0;finds=false;vis[S]=true;
    dfs(S,0,val);
    return finds;
}
void findpath(int u,int len,int val)
{
    if(u==T)
    {
        if(len==val) finds=true;
        return ;
    }
    if(len+dis[u]>val) return ;
    for(int v=1;v<=n;++v)
    {
        if(!vis[v]&&a[u][v]+len<=val)
        {
            vis[v]=true;
            findpath(v,len+a[u][v],val);
            vis[v]=false;
            if(finds) {pa[++cnt]=v;return ;}
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(a,0x3f,sizeof(a));
    scanf("%d%d%d",&n,&m,&k);
    int u,v,w,L=0,R=0;
    for(int i=1;i<=n;++i) a[i][i]=0;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        a[u][v]=a[v][u]=w;
        R+=w;
    }
    scanf("%d%d",&S,&T);
    spfa();
    while(L+1<R)
    {
        int M=(L+R)/2;
        if(test(M))
            R=M;
        else L=M;
    }
    if(test(L+1)) L=L+1;
    memset(vis,0,sizeof(vis));
    cnt=0;finds=false;
    vis[S]=true;
    findpath(S,0,L);
    pa[++cnt]=S;
    printf("%d %d\n",L,cnt);
    for(int i=cnt;i>=1;--i)
        printf("%d ",pa[i]);
    printf("\n");
    return 0;
}

