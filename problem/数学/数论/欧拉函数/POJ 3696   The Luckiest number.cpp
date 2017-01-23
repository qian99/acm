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
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b);}
int factor[500],num[500],cnt;
ll res;
ll euler_phi(ll n)
{
    int m=sqrt(n+0.5);
    ll ans=n;
    for(int i=2;i<=m;++i)
    {
        if(n%i==0)
        {
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans=ans-ans/n;
    return ans;
}
ll mul_mod(ll a,ll b,ll m)
{
    ll res=0;
    a%=m;b%=m;
    while(b)
    {
        if(b&1) res=(res+a)%m;
        a<<=1;
        if(a>=m) a%=m;
        b>>=1;
    }
    return res;
}
ll pow_mod(ll a,ll n,ll m)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=mul_mod(res,a,m);
        a=mul_mod(a,a,m);
        n>>=1;
    }
    return res;
}
void dfs(int pos,ll now,ll m)
{
    if(pos==cnt)
    {
        if(pow_mod(10,now,m)==1)
            res=min(res,now);
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=num[pos];++i)
    {
        dfs(pos+1,tmp*now,m);
        tmp*=factor[pos];
    }
}
void solve(ll n,ll m)
{
    int M=sqrt(n+0.5);
    cnt=0;
    for(int i=2;i<=M;++i)
    {
        if(n%i==0)
        {
            factor[cnt]=i;
            num[cnt]=0;
            while(n%i==0) {n/=i;num[cnt]++;}
            cnt++;
        }
    }
    if(n>1) {factor[cnt]=n;num[cnt++]=1;}
    res=m;
    dfs(0,1,m);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    ll L,m,d;
    while(~scanf("%I64d",&L))
    {
        if(L==0) break;
        tcase++;
        printf("Case %d: ",tcase);
        m=L/gcd(8,L)*9;
        if(gcd(10,m)!=1)
        {
            printf("0\n");
            continue;
        }
        d=euler_phi(m);
        solve(d,m);
        printf("%I64d\n",res);
    }
    return 0;
}
