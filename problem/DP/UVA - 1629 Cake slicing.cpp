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
const int maxn = 22;
int a[maxn][maxn];
int dp[maxn][maxn][maxn][maxn],n,m,k;
inline int cal(int x1,int y1,int x2,int y2)
{
    return a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1];
}
int f(int x1,int y1,int x2,int y2)
{
    if(cal(x1,y1,x2,y2) == 1) return 0;
    if(dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
    int & ans = dp[x1][y1][x2][y2] = inf;
    for(int i = x1;i < x2;++i)
    {
        if(cal(x1,y1,i,y2) && cal(i+1,y1,x2,y2))
            ans = min(ans,f(x1,y1,i,y2) + f(i+1,y1,x2,y2) + y2 - y1 + 1);
    }
    for(int i = y1;i < y2;++i)
    {
        if(cal(x1,y1,x2,i) && cal(x1,i+1,x2,y2))
            ans = min(ans,f(x1,y1,x2,i) + f(x1,i+1,x2,y2) + x2 - x1 + 1);
    }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int tcase = 0;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        memset(a,0,sizeof(a));
        int x, y;
        for(int i = 0;i < k;++i)
        {
            scanf("%d%d",&x,&y);
            a[x][y] = 1;
        }
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= m;++j)
                a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        memset(dp,0xff,sizeof(dp));
        int res = f(1,1,n,m);
        printf("Case %d: %d\n",++tcase,res);
    }
    return 0;
}
