#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 300000+10;
struct Node
{
    int u,v,w;
    bool operator < (const Node & a) const
    {
        return w < a.w;
    }
}node[maxn];
int dp[maxn],minv[maxn],S[maxn][2];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < m ;++i)
    {
        scanf("%d%d%d",&node[i].u,&node[i].v,&node[i].w);
    }
    sort(node , node + m);
    memset(dp,0,sizeof(dp));
    memset(minv,0,sizeof(minv));
    int ans = 0;
    for(int i = 0;i < m;)
    {
        int cnt = 0;
        while(node[i+cnt].w == node[i].w)
        {
            S[cnt][0] = node[i+cnt].v;
            S[cnt][1] = dp[node[i+cnt].u] + 1;
            cnt++;
        }
        for(int j = 0;j < cnt;++j)
            dp[S[j][0]] = max(dp[S[j][0]],S[j][1]);
        i += cnt;
    }
    for(int i = 1;i <= n;++i)
        ans = max(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}