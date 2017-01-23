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
const int maxn = 1000 + 10;
int a[maxn],b[maxn],dp[maxn],cnt[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&a[i]);
            b[i] = a[i];
        }
        sort(b,b + n);
        int m = unique(b,b + n) - b;
        for(int i = 0;i < n;++i)
            a[i] = lower_bound(b,b + m,a[i]) - b + 1;
        memset(dp,0,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        dp[a[0]] = 1;
        cnt[a[0]] = 1;
        for(int i = 1;i < n;++i)
        {
            int x = a[i];
            if(dp[x] == 0)
                dp[x] = 1;
            cnt[x]++;
            if(cnt[x] > 2) cnt[x] = 2;
            for(int j = x - 1;j > 0;--j)
            {
                if(dp[j] + 1 > dp[x])
                {
                    dp[x] = dp[j] + 1;
                    cnt[x] = cnt[j];
                }
                else if(dp[j] + 1 == dp[x])
                {
                    cnt[x] += cnt[j];
                    if(cnt[x] > 2) cnt[x] = 2;
                }
            }
        }
        int max1 = 0,max2 = 0;
        for(int i = n;i > 0;--i)
        {
            if(dp[i] > max1)
            {
                max2 = max1;
                max1 = dp[i];
                if(cnt[i] > 1) max2 = dp[i];
            }
            else if(dp[i] > max2)
                max2 = dp[i];
        }
        printf("%d\n",max2);
    }
    return 0;
}
