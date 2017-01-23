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
const int maxn = 200 + 10;
int color[maxn],cnt[maxn];
int dp[maxn][maxn][maxn];
int f(int l,int r,int x)
{
    if(l > r) return 0;
    if(l == r) return (cnt[l] + x)*(cnt[l] + x);
    if(dp[l][r][x] != -1) return dp[l][r][x];
    int & ans = dp[l][r][x];
    ans = f(l,r - 1,0) + (cnt[r] + x)*(cnt[r] + x);
    for(int i = l;i < r;++i)
        if(color[i] == color[r])
        {
            ans = max(ans,f(l,i,x + cnt[r]) + f(i+1,r - 1,0));
        }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n,tcase = 0 ;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(cnt,0,sizeof(cnt));
        for(int i = 1;i <= n;++i)
            scanf("%d",&color[i]);
        cnt[1] = 1;
        int m = 1;
        for(int i = 2;i <= n;++i)
            if(color[i] == color[m])
                cnt[m]++;
            else
            {
                color[++m] = color[i];
                cnt[m] = 1;
            }
        memset(dp,0xff,sizeof(dp));
        int ans = f(1,m,0);
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}
