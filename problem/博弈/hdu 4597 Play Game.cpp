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
const int maxn=25;
int dp[maxn][maxn][maxn][maxn],a[maxn],b[maxn];
bool vis[maxn][maxn][maxn][maxn];
int f(int x1,int y1,int x2,int y2,int tot)
{
    if(x1>y1&&x2>y2) return 0;
    if(x1>y1&&x2==y2) return b[x2];
    if(x1==y1&&x2>y2) return a[x1];
    if(vis[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
    int &ans=dp[x1][y1][x2][y2]=0;
    vis[x1][y1][x2][y2]=true;
    if(x1>y1)
        ans=tot-min(f(x1,y1,x2+1,y2,tot-b[x2]),f(x1,y1,x2,y2-1,tot-b[y2]));
    else if(x2>y2)
        ans=tot-min(f(x1+1,y1,x2,y2,tot-a[x1]),f(x1,y1-1,x2,y2,tot-a[y1]));
    else
    {
        ans=tot-min(f(x1,y1,x2+1,y2,tot-b[x2]),f(x1,y1,x2,y2-1,tot-b[y2]));
        ans=max(tot-f(x1+1,y1,x2,y2,tot-a[x1]),ans);
        ans=max(tot-f(x1,y1-1,x2,y2,tot-a[y1]),ans);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&b[i]);
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            sum+=a[i];
            sum+=b[i];
        }
        int res=f(1,n,1,n,sum);
        printf("%d\n",res);
    }
    return 0;
}
