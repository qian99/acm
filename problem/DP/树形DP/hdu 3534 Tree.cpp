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
    int v,w;
    int next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int maxv[maxn],cnt[maxn],maxpath;
ll ans;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    maxv[u]=0;
    cnt[u]=1;
    int tmp;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        tmp=maxv[v]+edges[k].w;
        if(tmp+maxv[u]>maxpath)
        {
            maxpath=tmp+maxv[u];
            ans=(ll)cnt[v]*cnt[u];
        }
        else if(tmp+maxv[u]==maxpath)
            ans+=(ll)cnt[u]*cnt[v];
        if(tmp>maxv[u])
        {
            cnt[u]=cnt[v];
            maxv[u]=tmp;
        }
        else if(tmp==maxv[u]) cnt[u]+=cnt[v];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        maxpath=0;ans=0;
        dfs(1,-1);
        printf("%d %I64d\n",maxpath,ans);
    }
    return 0;
}
