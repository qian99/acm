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
const int maxn=10000+100;
double dp[maxn],p;
bool flag[maxn];
int c[maxn],t[maxn],maxc,n;
inline int cal(int v)
{
    return floor((1.0+sqrt(5.0))/2.0*v*v);
}
double f(int x)
{
    if(x>maxc)
    {
        double res=0;
        for(int i=1;i<=n;++i)
            res+=p*t[i];
        return res;
    }
    if(flag[x]) return dp[x];
    flag[x]=true;
    dp[x]=0;
    for(int i=1;i<=n;++i)
    {
        if(x>c[i]) dp[x]+=p*t[i];
        else dp[x]+=p*(1+f(x+c[i]));
    }
    return dp[x];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int v;
    while(~scanf("%d%d",&n,&v))
    {
        memset(flag,0,sizeof(flag));
        maxc=-1;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&c[i]);
            maxc=max(maxc,c[i]);
            t[i]=cal(c[i]);
        }
        p=1.0/n;
        double ans=f(v);
        printf("%.3lf\n",ans);
    }
    return 0;
}
