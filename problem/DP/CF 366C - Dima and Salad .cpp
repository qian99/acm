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
const int maxn = 100 + 10;
int dp[maxn][200000 + 100];
int a[maxn],b[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    int bsum = 0;
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&b[i]);
        bsum += b[i];
    }
    memset(dp,0xff,sizeof(dp));
    int mid = 100000;
    dp[0][mid] = 0;
    int val , x;
    for(int i = 0;i < n;++i)
        for(int j = mid - bsum*m; j < 200000 + 100; j++)
        {
            if(dp[i][j] == -1) continue;
            dp[i+1][j] = max(dp[i+1][j],dp[i][j]);
            x = dp[i][j];
            x += a[i+1];
            val = j + a[i+1] - b[i+1]*m;
            dp[i+1][val] = max(dp[i+1][val],x);
        }
    int ans = -1;
    ans = dp[n][mid];
    if(ans == 0) ans = -1;
    printf("%d\n",ans);
    return 0;
}