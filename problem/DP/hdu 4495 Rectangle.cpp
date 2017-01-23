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
const int maxn=500+10;
char mat[maxn][maxn],a[maxn][maxn];
int dp[maxn][maxn],maxv,n,m;
void Rotate()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            a[m-j+1][i]=mat[i][j];
    swap(m,n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            mat[i][j]=a[i][j];
}
void solve()
{
    for(int i=0;i<=max(n,m);++i) dp[i][0]=dp[0][i]=0;
    int x,y,dx,dy,tmp;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            tmp=1;
            x=i;y=j-1;
            dx=i-1;dy=j;
            while(y>=1&&dx>=1)
            {
                if(mat[x][y]!=mat[dx][dy]) break;
                if(dp[i-1][j-1]+2<tmp+1) break;
                tmp++;
                y--;dx--;
            }
            dp[i][j]=tmp;
            maxv=max(maxv,dp[i][j]);
        }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%s",mat[i]+1);
        maxv=-1;
        solve();
        for(int i=0;i<3;++i)
        {
            Rotate();
            solve();
        }
        printf("%d\n",maxv*(maxv+1)/2);
    }
    return 0;
}
