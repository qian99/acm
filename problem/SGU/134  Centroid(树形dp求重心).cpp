#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int maxn=20000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge,n;
int dp[maxn],val[maxn],res[maxn],minval;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u]=1;
    val[u]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        dp[u]+=dp[v];
        val[u]=max(val[u],dp[v]);
    }
    val[u]=max(val[u],n-dp[u]);
    minval=min(minval,val[u]);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        minval=n;
        dfs(1,-1);
        int cnt=0;
        for(int i=1;i<=n;++i)
        {
            if(val[i]==minval)
              res[cnt++]=i;
        }
        sort(res,res+cnt);
        printf("%d %d\n",minval,cnt);
        printf("%d",res[0]);
        for(int i=1;i<cnt;++i)
          printf(" %d",res[i]);
    return 0;
}
