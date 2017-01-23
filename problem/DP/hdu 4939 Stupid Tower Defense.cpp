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
const int maxn = 1500+10;
ll dp[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int n,x,y,z,t;
        scanf("%d%d%d%d%d",&n,&x,&y,&z,&t);
        ll ans = (ll)x*t*n;
        int blue,green,red;
        ll damage;
        memset(dp,0,sizeof(dp));
        dp[0][0] = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j <= i;++j)
            {
                blue = j + 1;
                green = i - j;
                red = n - blue - green;
                damage = (ll)(t + j*z)*green*y;
                dp[i+1][j+1] = max(dp[i+1][j+1],dp[i][j]+damage);
                ans = max(ans,dp[i+1][j+1]+(ll)red*x*(t+blue*z)+(ll)red*y*green*(t+blue*z));

                blue--;green++;
                damage = (ll)(t + j*z)*(i-j)*y;
                dp[i+1][j] = max(dp[i+1][j],dp[i][j]+damage);
                ans = max(ans,dp[i+1][j]+(ll)red*x*(t+blue*z)+(ll)red*y*green*(t+blue*z));
            }
        printf("Case #%d: %I64d\n",++tcase,ans);
    }
    return 0;
}