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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=3000+10;
const int maxt=10000+10;
int dp[maxt];
struct Node
{
    int s,t;
    bool operator < (const Node &a) const
    {
        return (double)s/t<(double)a.s/a.t;
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,T;
    while(~scanf("%d%d",&n,&T))
    {
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
            scanf("%d%d",&node[i].t,&node[i].s);
        sort(node+1,node+n+1);
        for(int i=1;i<=n;++i)
        {
            for(int j=T;j>=node[i].t;--j)
                dp[j]=max(dp[j],dp[j-node[i].t]+j*node[i].s);
        }
        printf("%d\n",dp[T]);
    }
    return 0;
}
