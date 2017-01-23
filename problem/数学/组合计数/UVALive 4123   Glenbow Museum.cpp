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
ll dp[maxn][maxn][2][2];
ll f(int x,int y,int k,int p)
{
    if(x<0||y<0) return 0;
    if(x==1&&y==0&&k==0&&p==0) return 1;
    if(x==0&&y==1&&k==1&&p==1) return 1;
    if(x==0&&y==0) return 0;
    if(dp[x][y][k][p]!=-1) return dp[x][y][k][p];
    ll &ans=dp[x][y][k][p]=0;
    if(p==0) ans=f(x-1,y,k,0)+f(x-1,y,k,1);
    else ans=f(x,y-1,k,0);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int L,tcase=0;
    while(~scanf("%d",&L))
    {
        if(L==0) break;
        printf("Case %d: ",++tcase);
        if(L<=3||L&1)
        {
            printf("0\n");
            continue;
        }
        int x=(L+4)/2,y=(L-4)/2;
        ll ans=f(x,y,0,0)+f(x,y,0,1)+f(x,y,1,0);
//        cout<<f(x-1,y-1,0,1)<<endl;
        printf("%lld\n",ans);
    }
    return 0;
}
