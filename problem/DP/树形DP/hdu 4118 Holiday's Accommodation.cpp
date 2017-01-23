#include <iostream>
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
const int maxn=200000+10;
struct Edge
{
    int to;
    int w;
    int next;
};
int head[maxn],dp[maxn],nEdge,n;
Edge edges[maxn<<1];
ll ans;
void AddEdge(int u,int v,int w)
{
    edges[nEdge].to=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge++;
}
void dfs(int u,int fa)
{
    dp[u]=1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].to;
        int w=edges[k].w;
        if(v!=fa)
        {
            dfs(v,u);
            ans+=(ll)w*min(dp[v],n-dp[v]);
            dp[u]+=dp[v];
        }
    }
}
int main()
{
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        memset(dp,0,sizeof(dp));
        nEdge=0;ans=0;
        int a,b,c;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdge(a,b,c);
            AddEdge(b,a,c);
        }
        dfs(1,-1);
        printf("Case #%d: %I64d\n",tcase,ans*2);
    }
    return 0;
}
