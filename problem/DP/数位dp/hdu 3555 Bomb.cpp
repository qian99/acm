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
ll dp[64][4];
int num[64];
ll f(int pos,int st,bool limit)
{
    if(pos==-1) return (st&2)>>1;
    if(!limit&&dp[pos][st]!=-1)
        return dp[pos][st];
    int last=limit?num[pos]:9;
    int sn;
    ll ans=0;
    for(int i=0;i<=last;++i)
    {
        if(i==4) sn=(st|1);
        else if(i==9) sn=((st&1)<<1)|(st&2);
        else sn=(st&2);
        ans+=f(pos-1,sn,limit&&i==last);
    }
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
    memset(dp,0xff,sizeof(dp));
    ll n;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<cal(n)<<endl;
    }
    return 0;
}
