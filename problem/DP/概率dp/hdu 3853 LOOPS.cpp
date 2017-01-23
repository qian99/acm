#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
double dp[maxn][maxn],p1[maxn][maxn],p2[maxn][maxn],p3[maxn][maxn];
bool vis[maxn][maxn];
int m,n;
double f(int x,int y)
{
    if(x==m-1&&y==n-1) return 0;
    if(x>=m||y>=n) return 0;
    if(vis[x][y]) return dp[x][y];
    vis[x][y]=true;
    dp[x][y]=1;
    if(p2[x][y]!=0) dp[x][y]+=f(x,y+1)*p2[x][y];
    if(p3[x][y]!=0) dp[x][y]+=f(x+1,y)*p3[x][y];
//    dp[x][y]=1+f(x,y+1)*p2[x][y]+f(x+1,y)*p3[x][y];
    dp[x][y]/=(1.0-p1[x][y]);
    return dp[x][y];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=0;i<m;++i)
            for(int j=0;j<n;++j)
                scanf("%lf%lf%lf",&p1[i][j],&p2[i][j],&p3[i][j]);
        memset(vis,0,sizeof(vis));
        double ans=f(0,0);
        printf("%.3lf\n",ans*2);
    }
    return 0;
}