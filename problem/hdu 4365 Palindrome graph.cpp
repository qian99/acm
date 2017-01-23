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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int mod=100000007;
ll w[maxn];
map<pair<int,int>,int >mp;
ll pow_mod(ll x,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    w[1]=1;w[2]=1;
    for(int i=3;i<maxn;++i)
    {
        if(i&1) w[i]=w[i-2]+(i/2+1);
        else w[i]=w[i-2]+i/2;
    }
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        mp.clear();
        int sum=0;
        int x,y;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            x++;y++;
            if(mp.find(make_pair(x,y))!=mp.end()) continue;
            sum++;
            int dx=min(x,n-x+1);
            int dy=min(y,n-y+1);
            mp[make_pair(dx,dy)]=1;
            mp[make_pair(dx,n-dy+1)]=1;
            mp[make_pair(n-dx+1,dy)]=1;
            mp[make_pair(n-dx+1,n-dy+1)]=1;
            swap(dx,dy);
            mp[make_pair(dx,dy)]=1;
            mp[make_pair(dx,n-dy+1)]=1;
            mp[make_pair(n-dx+1,dy)]=1;
            mp[make_pair(n-dx+1,n-dy+1)]=1;
        }
        ll xx=w[n]-sum;
        ll ans=pow_mod(k,xx);
        printf("%I64d\n",ans);
    }
    return 0;
}
