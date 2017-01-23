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
const int maxn=100000+10;
const int mod=1000000000+7;
ll num[maxn],a[maxn];
ll f(ll x,ll y)
{
    ll res=1,b=x;
    while(y)
    {
        if(y&1) res=(res*b)%mod;
        b=(b*b)%mod;
        y>>=1;
    }
    return res;
}
ll cal(ll x,ll y)
{
    ll ret=0;
    while(x&&(x%y==0))
    {
        ret++;
        x/=y;
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,x;
    while(~scanf("%d%d",&n,&x))
    {
        ll sum=0;
        for(int i=0;i<n;++i)
        {
            scanf("%I64d",&a[i]);
            sum+=a[i];
        }
        for(int i=0;i<n;++i)
          num[i]=sum-a[i];
        sort(num,num+n);
        ll cnt=0,ont=1,op=num[0],tmp;
        int p=0;
        while(true)
        {
            while(p+1<n&&num[p+1]-cnt==op) ont++,p++;
            cnt+=op;
            if((ont%x)||(op==0))
            {
                tmp=min(cnt,sum);
                ll ans=f(x,tmp);
                printf("%I64d\n",ans);
                break;
            }
            op=cal(ont,x);
            if(p+1<n) op=min(op,num[p+1]-cnt);
            for(int i=0;i<op;++i) ont/=x;
        }
    }
    return 0;
}
