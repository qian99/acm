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
const int maxn = 41;
int dp[maxn][maxn][maxn][maxn],n;
int color[4][maxn],sum[4][maxn][maxn];
int cnt[22],remain;
int f(int a,int b,int c,int d)
{
    if(a == n && b == n && c == n && d == n) return 0;
    if(dp[a][b][c][d] != -1) return dp[a][b][c][d];
    int & ans = dp[a][b][c][d] = 0;
    if(remain >= 5) return ans = 0;
    if(a < n)
    {
        if(cnt[color[0][a+1]] & 1)
        {
            cnt[color[0][a+1]]++;
            remain--;
            ans = max(ans,f(a+1,b,c,d) + 1);
            cnt[color[0][a+1]]--;
            remain++;
        }
        else
        {
            cnt[color[0][a+1]]++;
            remain++;
            ans = max(ans,f(a+1,b,c,d));
            cnt[color[0][a+1]]--;
            remain--;
        }
    }
    if(b < n)
    {
        if(cnt[color[1][b+1]] & 1)
        {
            cnt[color[1][b+1]]++;
            remain--;
            ans = max(ans,f(a,b+1,c,d) + 1);
            cnt[color[1][b+1]]--;
            remain++;
        }
        else
        {
            cnt[color[1][b+1]]++;
            remain++;
            ans = max(ans,f(a,b+1,c,d));
            cnt[color[1][b+1]]--;
            remain--;
        }
    }
    if(c < n)
    {
        if(cnt[color[2][c+1]] & 1)
        {
            cnt[color[2][c+1]]++;
            remain--;
            ans = max(ans,f(a,b,c+1,d) + 1);
            cnt[color[2][c+1]]--;
            remain++;
        }
        else
        {
            cnt[color[2][c+1]]++;
            remain++;
            ans = max(ans,f(a,b,c+1,d));
            cnt[color[2][c+1]]--;
            remain--;
        }
    }
    if(d < n)
    {
        if(cnt[color[3][d+1]] & 1)
        {
            cnt[color[3][d+1]]++;
            remain--;
            ans = max(ans,f(a,b,c,d+1) + 1);
            cnt[color[3][d+1]]--;
            remain++;
        }
        else
        {
            cnt[color[3][d+1]]++;
            remain++;
            ans = max(ans,f(a,b,c,d+1));
            cnt[color[3][d+1]]--;
            remain--;
        }
    }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        memset(sum,0,sizeof(sum));
        memset(dp,0xff,sizeof(dp));
        for(int i = 1;i <= n;++i)
            for(int j = 0;j < 4;++j)
            {
                scanf("%d",&color[j][i]);
                sum[j][i][color[j][i]] = 1;
            }
        for(int i = 0;i < 4;++i)
            for(int j = 1;j <= n;++j)
                for(int k = 1;k <= 20;++k)
                    sum[i][j][k] += sum[i][j-1][k];
        memset(cnt,0,sizeof(cnt));
        remain = 0;
        int ans = f(0,0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
