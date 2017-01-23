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
double dp[maxn][maxn][2];
bool flag[maxn][maxn][2];
double f(int x,int y,int turns)
{
    if(x<0||y<0) return 0;
    if(x==0&&y==0) return 0;
    if(flag[x][y][turns]) return dp[x][y][turns];
    flag[x][y][turns]=true;
    if(turns==0)
        dp[x][y][turns]=(double)x/(x+y)+(double)y/(x+y)*f(x,y-1,turns^1);
    else
    {
        if(y!=0&&x!=0)
            dp[x][y][turns]=(double)y/(x+y)*((double)(y-1)/(x+y-1)*f(x,y-2,turns^1)+(double)x/(x+y-1)*f(x-1,y-1,turns^1));
        else dp[x][y][turns]=0;
    }
    return dp[x][y][turns];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int w,b;
    memset(flag,0,sizeof(flag));
    while(~scanf("%d%d",&w,&b))
    {
        printf("%.9lf\n",f(w,b,0));
    }
    return 0;
}
