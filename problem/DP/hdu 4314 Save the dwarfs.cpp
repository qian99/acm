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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 2000 + 10;
struct Node
{
    int A,B;
    Node(int A = 0,int B = 0):A(A),B(B){}
    bool operator < (const Node & a) const
    {
        return A + B > a.A + a.B;
    }
}node[maxn];
int dp[maxn][maxn],sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,H;
    while(~scanf("%d",&n))
    {
        for(int i = 1;i <= n;++i)
            scanf("%d%d",&node[i].A,&node[i].B);
        scanf("%d",&H);
        sort(node + 1, node + n + 1);
        sum[0] = 1;
        for(int i = 1;i <= n;++i)
            sum[i] = sum[i-1] + node[i].A;
        memset(dp,0x3f,sizeof(dp));
        dp[0][0] = 0;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= i;++j)
            {
                dp[i][j] = dp[i-1][j] - node[i].A;
                dp[i][j] = min(dp[i][j],max(dp[i-1][j-1],H - sum[i] -node[i].B));
            }
        int ans = 0;
        for(int i = n;i >= 0;--i)
            if(dp[n][i] <= 0)
            {
                ans = i;
                break;
            }
        printf("%d\n",ans);
    }
    return 0;
}
