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
const int maxn=500000+10;
struct Edge
{
    int v,next;
}edges[maxn];
int head[maxn],dp[maxn][2],flag[maxn],nEdge;
int ans[maxn],cnt;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u)
{
    dp[u][0]=0;dp[u][1]=1;
    int sum=0,tmp=inf;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
//        if(v==fa) continue;
        dfs(v);
        dp[u][1]+=dp[v][0];
        sum+=dp[v][0];
        if(dp[v][0]-dp[v][1]<tmp)
        {
            tmp=dp[v][0]-dp[v][1];
            flag[u]=v;
        }
    }
    dp[u][0]=max(sum,sum-tmp);
}
void dfs2(int u,int s)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
//        if(v==fa) continue;
        if(s==1) dfs2(v,0);
        else
        {
            if(flag[u]!=v)
              dfs2(v,0);
            else
            {
                ans[cnt++]=v;
                dfs2(v,1);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int v;
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&v);
        AddEdge(v,i);
    }
    dfs(1);
    printf("%d\n",dp[1][0]*1000);
    cnt=0;
    dfs2(1,0);
    sort(ans,ans+cnt);
    for(int i=0;i<cnt;++i)
    {
        if(i) printf(" ");
        printf("%d",ans[i]);
    }
    printf("\n");
    return 0;
}
