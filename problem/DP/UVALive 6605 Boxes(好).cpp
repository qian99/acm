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
const int maxn = 100 + 10;
const int maxm = 1000 + 10;
const int mod = 10007;
int C[maxn][maxn],dp[2][maxn][maxm];
int w[maxn],cnt[maxn],prec[maxn],sumw[maxn],sum[maxn];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0] = 1;
    for(int i = 1;i < maxn;++i)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++j)
        {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
            if(C[i][j] >= mod) C[i][j] -= mod;
        }
    }
}
inline void Update(int & a,int b)
{
    a += b;
    if(a >= mod) a -= mod;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,W;
        scanf("%d%d",&n,&W);
        for(int i = 1;i <= n;++i)
            scanf("%d",&w[i]);
        sort(w + 1, w + n + 1);
        int m = 1;
        cnt[1] = 1;
        for(int i = 2;i <= n;++i)
            if(w[i] == w[m])
                cnt[m]++;
            else
                w[++m] = w[i],cnt[m] = 1;
        sum[0] = sumw[0] = 0;
        prec[0] = 1;
        for(int i = 1;i <= m;++i)
        {
            sum[i] = sum[i-1] + cnt[i];
            sumw[i] = sumw[i-1] + cnt[i]*w[i];
            prec[i] = prec[i-1]*C[sum[i]][cnt[i]]%mod;
        }
        memset(dp,0,sizeof(dp));
        int p  = 0,ans = 0;
        dp[0][0][0] = 1;
        for(int i = m;i >= 1;--i)
        {
            memset(dp[p^1],0,sizeof(dp[p^1]));
            for(int j = 0;j <= n;++j)
                for(int k = 0;k <= W;++k)
                {
                    if(dp[p][j][k] == 0) continue;
                    for(int x = 0;x <= cnt[i] && k + x*w[i] <= W;++x)
                        Update(dp[p^1][j + x][k + x*w[i]],dp[p][j][k]*C[j + x][x]%mod);
                    if(sumw[i - 1] + k <= W && sumw[i - 1] + k + cnt[i]*w[i] > W)
                    {
                        int x = (W - sumw[i - 1] - k)/w[i];
                        Update(ans,dp[p][j][k]*C[j + x][x]%mod*prec[i-1]%mod*C[j + x + sum[i-1]][j + x]%mod);
                    }
                }
            p ^= 1;
        }
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}

