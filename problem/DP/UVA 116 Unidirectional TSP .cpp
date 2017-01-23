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
int dp[maxn][11],cost[maxn][11],path[maxn][11],m,n;
int f(int y,int x)
{
    if(y == n) return cost[y][x];
    if(dp[y][x] != -1) return dp[y][x];
    dp[y][x] = inf;
    int dx , tmp;
    for(int i = -1;i <= 1;++i)
    {
        dx = x + i;
        if(dx <= 0) dx = m;
        else if(dx > m) dx = 1;
        tmp = f(y+1,dx) + cost[y][x];
        if(tmp < dp[y][x])
        {
            dp[y][x] = tmp;
            path[y][x] = dx;
        }
        else if(tmp == dp[y][x])
            path[y][x] = min(path[y][x],dx);
    }
    return dp[y][x];
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        for(int i = 1;i <= m;++i)
            for(int j = 1;j <= n;++j)
                scanf("%d",&cost[j][i]);
        memset(dp,0xff,sizeof(dp));
        int ans = inf,pos;
        for(int i = 1;i <= m;++i)
            if(f(1,i) < ans)
            {
                ans = f(1,i);
                pos = i;
            }
        printf("%d",pos);
        for(int j = 1;j < n;++j)
        {
            printf(" %d",path[j][pos]);
            pos = path[j][pos];
        }
        printf("\n%d\n",ans);
    }
    return 0;
}
