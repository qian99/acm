#include<iostream>
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
typedef long long ll;
const int maxn=100000+10;
struct Edge
{
    int u,v,w;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int pt[maxn],cntp,wp,sp,maxlen;
int d[maxn],num[maxn],dp[maxn][2],cnt;
ll ans;
bool vis[maxn<<1];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].u=u;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    nEdge=-1;
}
void f(int u,int fa)
{
    dp[u][0]=dp[u][1]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        f(v,u);
        int tmp=dp[v][0]+edges[k].w;
        if(tmp>dp[u][0])
        {
            dp[u][1]=dp[u][0];
            dp[u][0]=tmp;
        }
        else if(tmp>dp[u][1])
            dp[u][1]=tmp;
    }
}
void findroot(int u,int fa)
{
    pt[u]=1;
    int maxp=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||vis[k]) continue;
        findroot(v,u);
        maxp=max(maxp,pt[v]);
        pt[u]+=pt[v];
    }
    maxp=max(maxp,cntp-pt[u]);
    if(maxp<wp)
    {
        wp=maxp;
        sp=u;
    }
}
void dfs(int u,int fa)
{
    pt[u]=1;
    num[cnt++]=d[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||vis[k])continue;
        d[v]=d[u]+edges[k].w;
        dfs(v,u);
        pt[u]+=pt[v];
    }
}
ll cal(int x,int s)
{
    d[x]=s;cnt=0;
    dfs(x,-1);
    sort(num,num+cnt);
    int l=0,r=cnt-1;
    ll res=0;
    int ca,cb;
    while(l<r)
    {
        if(num[l]+num[r]==maxlen)
        {
            ca=cb=0;
            if(num[l]==num[r])
            {
                res+=(ll)(r-l+1)*(r-l)/2;
                break;
            }
            while(num[l+ca]+num[r]==maxlen&&l+ca<r) ca++;
            while(num[l]+num[r-cb]==maxlen&&l<r-cb) cb++;
            res+=(ll)ca*cb;
            l+=ca;r-=cb;
        }
        else if(num[l]+num[r]>maxlen)
          r--;
        else l++;
    }
    return res;
}
void work(int x)
{
    ans+=cal(x,0);
    for(int k=head[x];k!=-1;k=edges[k].next)
    {
        if(vis[k]) continue;
        int v=edges[k].v;
        vis[k]=vis[k^1]=true;
        ans-=cal(v,edges[k].w);
        cntp=pt[v];wp=inf;
        findroot(v,-1);
        work(sp);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        maxlen=0;
        f(1,-1);
        for(int i=1;i<=n;++i)
          maxlen=max(maxlen,dp[i][0]+dp[i][1]);
        cntp=wp=n;ans=0;
        findroot(1,-1);
        work(sp);
        printf("%d %I64d\n",maxlen,ans);
    }
    return 0;
}
