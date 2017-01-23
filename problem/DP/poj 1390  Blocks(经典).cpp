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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
int dp[maxn][maxn][maxn];
int color[maxn],num[maxn];
inline int cal(int x) { return x*x; }
int f(int l,int r,int k)
{
    if(l>r) return 0;
    if(l==r) return dp[l][r][k]=cal(num[l]+k);
    if(dp[l][r][k]!=-1) return dp[l][r][k];
    int &ans=dp[l][r][k];
    ans=f(l,r-1,0)+cal(num[r]+k);
    for(int i=l;i<r;++i)
    {
        if(color[i]==color[r])
            ans=max(ans,f(l,i,num[r]+k)+f(i+1,r-1,0));
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        memset(dp,0xff,sizeof(dp));
        int n,m=0,v;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&v);
            if(m==0) color[m]=v,num[m++]=1;
            else if(color[m-1]==v) num[m-1]++;
            else
            {
                color[m]=v;
                num[m++]=1;
            }
        }
        printf("Case %d: %d\n",++tcase,f(0,m-1,0));
    }
    return 0;
}
