#include <iostream>
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

#pragma comment(linker, "/STACK:16777216")

using namespace std;
typedef  __int64 ll;
const int maxn=100000+10;
vector<int>G[maxn];
ll dp[maxn],twol[maxn],num[maxn];
void dfs(int u,int fa)
{
    dp[u]=twol[u]=0;
    num[u]=1;
    int cnt=0;
    ll sum=0,sum2=0;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v!=fa)
        {
            cnt++;
            dfs(v,u);
            num[u]+=num[v];
            twol[u]+=twol[v]+num[v];
            dp[u]+=dp[v]+twol[v];
            sum+=num[v];
            sum2+=twol[v];
        }
    }
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v!=fa)
        {
            sum-=num[v];
            dp[u]+=num[v]*sum;
            dp[u]+=num[v]*(sum2-twol[v]);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<=n;++i) G[i].clear();
        int a,b;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        dfs(1,-1);
        ll total=((ll)n*(n-1)/2)*(n-2)/3;
        printf("%I64d\n",total-dp[1]);
    }
    return 0;
}
