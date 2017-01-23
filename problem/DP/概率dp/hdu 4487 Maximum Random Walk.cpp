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
const int Base = 100;
double dp[maxn][maxn*2],L,R;
int vis[maxn][maxn*2],T;
double f(int remain,int limit)
{
    if(remain == 0) return 1;
    if(vis[remain][limit] == T) return dp[remain][limit];
    vis[remain][limit] = T;
    double & ans = dp[remain][limit] = 0;
    ans = f(remain - 1,limit + 1)*L + f(remain - 1,limit)*(1.0 - L - R);
    if(limit > 0)
        ans += f(remain - 1,limit - 1)*R;
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase;
    T = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        T++;
        scanf("%d%d%lf%lf",&tcase,&n,&L,&R);
        double ans = 0;
        for(int i = 1;i <= n;++i)
        {
            ans += (f(n,i) - f(n,i - 1))*i;
        }
        printf("%d %.4lf\n",tcase,ans);
    }
    return 0;
}
