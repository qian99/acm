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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
double dp[maxn][maxn];
bool flag[maxn][maxn];
int n,s;
double f(int x,int y)
{
    if(x==n&&y==s) return 0;
    if(x>n||y>s) return 0;
    if(flag[x][y]) return dp[x][y];
    flag[x][y]=true;
    dp[x][y]=f(x+1,y)*(n-x)/n*y/s+f(x,y+1)*x/n*(s-y)/s+1;
    dp[x][y]+=f(x+1,y+1)*(n-x)/n*(s-y)/s;
    dp[x][y]/=(1-(double)x*y/n/s);
    return dp[x][y];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&s))
    {
        memset(flag,0,sizeof(flag));
        double ans=f(0,0);
        printf("%.4lf\n",ans);
    }
    return 0;
}
