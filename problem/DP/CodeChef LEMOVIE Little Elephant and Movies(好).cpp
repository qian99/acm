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
const int maxn = 200 + 10;
const int mod = 1e9 + 7;
int C[maxn][maxn],dp[maxn][maxn];
int a[maxn],cnt[maxn],F[maxn];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0] = 1;
    for(int i = 1;i < maxn;++i)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++j)
        {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if(C[i][j] >= mod) C[i][j] -= mod;
        }
    }
    F[0] = 1;
    for(int i = 1;i < maxn;++i)
        F[i] = (ll)F[i - 1]*i%mod;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        sort(a + 1, a + n + 1);
        reverse(a + 1,a + n + 1);
        memset(cnt,0,sizeof(cnt));
        int m = 0;
        cnt[++m] = 1;
        for(int i = 2;i <= n;++i)
        {
            if(a[i] == a[m])
                cnt[m]++;
            else
                a[++m] = a[i],cnt[m] = 1;
        }
        n = m;
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j <= n;++j)
            {
                if(dp[i][j] == 0) continue;
                if(cnt[i])
                    dp[i + 1][j] = (dp[i + 1][j] + (ll)dp[i][j]*C[cnt[i] + cnt[i+1] - 1][cnt[i+1]]%mod*F[cnt[i+1]])%mod;
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + (ll)dp[i][j]*C[cnt[i] + cnt[i+1] - 1][cnt[i+1]-1]%mod*F[cnt[i+1]])%mod;
            }
            cnt[i + 1] += cnt[i];
        }
        int ans = 0;
        for(int i = 0;i <= k;++i)
            ans = (ans + dp[n][i])%mod;
        printf("%d\n",ans);
    }
    return 0;
}
