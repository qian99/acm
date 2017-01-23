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
const int maxn = 55;
double dp[maxn][maxn][maxn*maxn];
int vis[maxn][maxn][maxn*maxn],cnt,n,m;
double f(int r,int c,int x)
{
    if(r == n && c == m) return 0;
    if(vis[r][c][x] == cnt) return dp[r][c][x];
    vis[r][c][x] = cnt;
    dp[r][c][x] = 0;
    double tot = n*m - x;
    int addr = c*n - r*c;
    int addc = r*m - r*c;
    int add = n*m - (r*m + c*n - r*c);
    int remain = tot - addr - addc - add;
    if(addr) dp[r][c][x] += addr/tot*f(r + 1,c,x + 1);
    if(addc) dp[r][c][x] += addc/tot*f(r,c + 1,x + 1);
    if(add)  dp[r][c][x] += add/tot*f(r + 1,c + 1,x + 1);
    if(remain) dp[r][c][x] += remain/tot*f(r,c,x + 1);
    dp[r][c][x]++;
    return dp[r][c][x];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    cnt = 0;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        cnt++;
        printf("%.10lf\n",f(0,0,0));
    }
    return 0;
}
