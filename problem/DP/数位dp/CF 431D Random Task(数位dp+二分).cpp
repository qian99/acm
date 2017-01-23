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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
int num[maxn],k;
ll dp[maxn][maxn];
ll f(int pos,int x,bool limit)
{
    if(pos==-1) return x==k;
    if(!limit&&dp[pos][x]!=-1) return dp[pos][x];
    ll ans=0;
    int last=limit?num[pos]:1;
    for(int i=0;i<=last;++i)
        ans+=f(pos-1,x+i,limit&&i==last);
    if(!limit) dp[pos][x]=ans;
    return ans;
}
ll cal(ll x,int type)
{
    memset(dp,0xff,sizeof(dp));
    int len=0;
    if(type) num[len++]=0;
    while(x)
    {
        num[len++]=x&1;
        x>>=1;
    }
    return f(len-1,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll m;
    cin>>m>>k;
    ll L=1,R=1000000000000000001LL;
    ll tmp,ans;
    while(L<R)
    {
        ll mid=(L+R)>>1;
        tmp=cal(mid,1)-cal(mid,0);
        if(tmp>m) R=mid;
        else if(tmp<m) L=mid;
        else
        {
            ans=mid;
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}