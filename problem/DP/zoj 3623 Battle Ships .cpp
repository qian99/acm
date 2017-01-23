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
const int maxn=55;
const int maxm=500+10;
int dp[maxm][maxm],t[maxn],l[maxn],n;
int f(int def,int att)
{
    if(def<=0) return 0;
    if(att>=def) return 1;
    if(dp[def][att]!=-1) return dp[def][att];
    int &ans=dp[def][att]=inf;
    if(att>0) ans=def/att+((def%att)?1:0);
    for(int i=1;i<=n;++i)
        ans=min(ans,f(def-att*t[i],att+l[i])+t[i]);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int L;
    while(~scanf("%d%d",&n,&L))
    {
        memset(dp,0xff,sizeof(dp));
        for(int i=1;i<=n;++i)
            scanf("%d%d",&t[i],&l[i]);
        printf("%d\n",f(L,0));
    }
    return 0;
}
