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
int d[100],a[100],cnt;
int n,m;
void getd(int m)
{
    cnt=0;
    for(ll i=2;i*i<=m;++i)
    {
        if(m%i==0)
        {
            d[cnt++]=i;
            while(m%i==0) m/=i;
        }
    }
    if(m>1) d[cnt++]=m;
}
ll pows(ll x,ll n)
{
    ll res=1;
    for(int i=0;i<n;++i)
        res*=x;
    return res;
}
ll dfs(int pos,int sp,int tot)
{
    if(pos==tot)
    {
        ll tmp=m;
        for(int i=0;i<tot;++i)
            tmp/=a[i];
        return pows(tmp,n);
    }
    ll sum=0;
    for(int i=sp;i<cnt;++i)
    {
        a[pos]=d[i];
        sum+=dfs(pos+1,i+1,tot);
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    getd(m);
    ll ans=pows(m,n),tmp;
    for(int i=1;i<=cnt;++i)
    {
        tmp=dfs(0,0,i);
        if(i&1) ans-=tmp;
        else ans+=tmp;
    }
    printf("%lld\n",ans);
    return 0;
}
