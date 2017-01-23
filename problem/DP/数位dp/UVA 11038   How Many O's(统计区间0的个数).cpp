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
int num[20];
ll dp[20][20][2];
ll f(int pos,int cnt,int st,bool limit)
{
    if(pos==-1) return st?cnt:1;
    if(!limit&&dp[pos][cnt][st]!=-1) return dp[pos][cnt][st];
    int last=limit?num[pos]:9;
    ll ans=0,tmp;
    for(int i=0;i<=last;++i)
    {
        tmp=cnt;
        if(st&&i==0) tmp++;
        ans+=f(pos-1,tmp,st|(i!=0),limit&&i==last);
    }
    if(!limit) dp[pos][cnt][st]=ans;
    return ans;
}
ll cal(ll x)
{
    if(x==-1) return 0;
    int len=0;
    while(x)
    {
        num[len++]=x%10;
        x/=10;
    }
    return f(len-1,0,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll m,n;
    while(~scanf("%lld%lld",&m,&n))
    {
        if(m==-1&&n==-1) break;
        memset(dp,0xff,sizeof(dp));
        printf("%lld\n",cal(n)-cal(m-1));
    }
    return 0;
}
