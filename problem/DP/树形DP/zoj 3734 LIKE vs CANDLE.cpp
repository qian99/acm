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
const int maxn=50000+10;
struct Edge
{
    int v,next;
}edges[maxn];
int head[maxn],nEdge;
int n,X,Y,val[maxn],S[maxn];
int dp[maxn][2];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int side)
{
    if(side) val[u]=-val[u];
    dp[u][0]=val[u];dp[u][1]=-val[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        dfs(v,side^S[v]);
        dp[u][0]+=max(dp[v][0],dp[v][1]-(S[v]?Y:X));
        dp[u][1]+=max(dp[v][1],dp[v][0]-(S[v]?Y:X));
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&X,&Y))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int v,tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d%d",&val[i],&v,&S[i],&tmp);
            if(tmp) val[i]=-val[i];
            AddEdge(v,i);
        }
        S[0]=val[0]=0;
        dfs(0,0);
        if(dp[0][0]<0) printf("HAHAHAOMG\n");
        else printf("%d\n",dp[0][0]);
    }
    return 0;
}
