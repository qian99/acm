#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll dp[20][22],n,k;
int num[20];
ll f(int pos,int st,bool limit)
{
    if(pos==-1) return (st==k)?1:0;
    if(!limit&&dp[pos][st]!=-1) return dp[pos][st];
    ll ans=0;
    int last=limit?num[pos]:9;
    for(int i=0;i<=last;++i)
        ans+=f(pos-1,st^i,limit&&i==last);
    if(!limit) dp[pos][st]=ans;
    return ans;
}
ll cal(ll x)
{
    int len=0;
    while(x)
    {
        num[len++]=x%10;
        x/=10;
    }
    return f(len-1,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%I64d%I64d",&n,&k))
    {
        memset(dp,0xff,sizeof(dp));
        if(k>20)
        {
            printf("0\n");
            continue;
        }
        ll ans=cal(n);
        if(k==0) ans--;
        printf("%I64d\n",ans);
    }
    return 0;
}