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
const int maxn = 2100 + 10;
struct Node
{
    int H,W;
    Node(int H = 0,int W = 0):H(H),W(W){}
    bool operator < (const Node & a) const
    {
        return H > a.H;
    }
}node[maxn];
int dp[2][maxn][maxn],sumw[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%d%d",&node[i].H,&node[i].W);
        sort(node + 1, node + n + 1);
        sumw[0] = 0;
        for(int i = 1;i <= n;++i)
            sumw[i] = sumw[i-1] + node[i].W;
        memset(dp[1],0x3f,sizeof(dp[1]));
        dp[1][0][0] = 0;
        int H,W;
        for(int i = 1;i < n;++i)
        {
            int p = i & 1;
            for(int j = 0;j <= sumw[i+1];++j)
                for(int k = 0;k + j <= sumw[i+1];++k)
                    dp[p^1][j][k] = inf;
            H = node[i+1].H;
            W = node[i+1].W;
            for(int j = 0;j <= sumw[i];++j)
                for(int k = 0;k + j <= sumw[i];++k)
                {
                    if(dp[p][j][k] == inf) continue;
                    dp[p^1][j][k] = min(dp[p^1][j][k],dp[p][j][k]);
                    dp[p^1][j + W][k] = min(dp[p^1][j + W][k],dp[p][j][k] + (j?0:H));
                    dp[p^1][j][k + W] = min(dp[p^1][j][k + W],dp[p][j][k] + (k?0:H));
                }
        }
        int ans = inf;
        for(int i = 1;i <= sumw[n];++i)
            for(int j = 1;i + j <= sumw[n];++j)
            {
                if(dp[n&1][i][j] == inf) continue;
                W = max(i,j);
                W = max(W,sumw[n] - i - j);
                H = node[1].H + dp[n&1][i][j];
                ans = min(ans,W*H);
            }
        printf("%d\n",ans);
    }
    return 0;
}
