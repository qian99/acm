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
const int maxn=100+10;
int dp[maxn][11][11][11][11],A[11],B[11];
int m,n;
int f(int x,int a,int b,int c,int d)
{
    if(x>=m) return 0;
    if(dp[x][a][b][c][d]!=-1) return dp[x][a][b][c][d];
    int &ans=dp[x][a][b][c][d];
    ans=inf;
    for(int i=1;i<=n;++i)
    {
        if(i!=a&&i!=b&&i!=c&&i!=d)
            ans=min(ans,f(x+A[i],b,c,d,i)+1);
        else if(i==d)
        {
            if(B[i]<=0) ans=min(ans,f(x+A[i],b,c,d,i)+1);
        }
        else if(i==c)
        {
            if(B[i]<=1)
                ans=min(ans,f(x+A[i],b,c,d,i)+1);
        }
        else if(i==b)
        {
            if(B[i]<=2) ans=min(ans,f(x+A[i],b,c,d,i)+1);
        }
        else if(i==a)
        {
            if(B[i]<=3) ans=min(ans,f(x+A[i],b,c,d,i)+1);
        }
    }
    if(a||b||c||d) ans=min(ans,f(x,b,c,d,0)+1);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&A[i],&B[i]);
    memset(dp,0xff,sizeof(dp));
    int ans=f(0,0,0,0,0);
    printf("%d\n",ans);
    return 0;
}
