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
const int maxn=100000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge,n,k;
ll dp[maxn],ans;
int cnt[maxn];
bool flag[maxn];
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
    dp[u]=Inf;
    if(flag[u]) cnt[u]=1;
    ll tmp=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        if(!cnt[v]) continue;
        if(flag[u])
          ans+=min((ll)edges[k].w,dp[v]);
        else
        {
            ans+=min(tmp,min(dp[v],(ll)edges[k].w));
            tmp=max(tmp,min(dp[v],(ll)edges[k].w));
            if(dp[u]==Inf) dp[u]=tmp;
            else dp[u]=max(tmp,dp[u]);
        }
    }
    if(tmp) cnt[u]=1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        memset(head,0xff,sizeof(head));
        memset(flag,0,sizeof(flag));
        memset(cnt,0,sizeof(cnt));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        for(int i=0;i<k;++i)
        {
            scanf("%d",&u);
            flag[u]=true;
        }
        ans=0;
        dfs(0,-1);
        printf("%I64d\n",ans);
    }
    return 0;
}
