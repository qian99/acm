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
const int maxn = 1000 + 10;
const int maxm = 10000  + 10;
double dp[2][maxm];
int X[maxn],path[maxn][maxm],ans[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,Y;
    scanf("%d%d%d",&n,&m,&Y);
    for(int i = 1;i <= n;++i)
        scanf("%d",&X[i]);
    for(int i = 0; i <= m;++i)
        dp[0][i] = 1e10;
    double tmp;
    dp[0][m] = 1;
    for(int i = 0;i < n; ++i)
    {
        int p = i&1;
        for(int j = 0;j <= m;++j) dp[p^1][j] = 1e10;
        tmp = (double)X[i+1]/Y;
        int getcion = tmp*m;
        for(int j = getcion; j <= m; ++j)
        {
            if(dp[p][j] == 1e10) continue;
            if(dp[p^1][j-getcion] > dp[p][j] + abs(tmp-(double)getcion/m))
            {
                dp[p^1][j-getcion] = dp[p][j] + abs(tmp-(double)getcion/m);
                path[i+1][j-getcion] = getcion;
            }
            if(j == getcion) continue;
            if(dp[p^1][j-getcion-1] > dp[p][j] + abs(tmp-(double)(getcion+1)/m))
            {
                dp[p^1][j-getcion-1] = dp[p][j] + abs(tmp-(double)(getcion+1)/m);
                path[i+1][j-getcion-1] = getcion+1;
            }
        }
    }
    int pos = 0;
    for(int i = n; i >= 1; --i)
    {
        ans[i] = path[i][pos];
        pos += path[i][pos];
    }
    for(int i = 1; i <= n;++i)
    {
        if(i > 1) printf(" ");
        printf("%d",ans[i]);
    }
    printf("\n");
    return 0;
}
