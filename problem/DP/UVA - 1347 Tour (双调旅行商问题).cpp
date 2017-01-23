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
struct Point
{
    int x,y;
    Point(int x = 0,int y = 0):x(x),y(y){}
}pt[maxn];
double dp[maxn][maxn],d[maxn][maxn];
bool vis[maxn][maxn];
int n;
inline double Len(Point a, Point b)
{
    return sqrt((double)(a.x - b.x)*(a.x - b.x) + (double)(a.y - b.y)*(a.y - b.y));
}
double f(int x,int y)
{
    if(x == n) return d[n][y];
    if(vis[x][y]) return dp[x][y];
    vis[x][y] = true;
    double res = 1e10,tmp;
    tmp = f(x + 1,y) + d[x][x+1];
    res = min(res,tmp);
    tmp = f(x+1,x) + d[y][x+1];
    res = min(res,tmp);
    return dp[x][y] = res;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(vis,0,sizeof(vis));
        for(int i = 1;i <= n;++i)
            scanf("%d%d",&pt[i].x,&pt[i].y);
        for(int i = 1;i <= n;++i)
            for(int j = i + 1;j <= n;++j)
                d[i][j] = d[j][i] = Len(pt[i],pt[j]);
        double ans = f(2,1) + d[1][2];
        printf("%.2lf\n",ans);
    }
    return 0;
}
