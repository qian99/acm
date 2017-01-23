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
const int Maxt=20;
ll mul_mod(ll a,ll b,ll c)
{
    ll ret=0;
    a%=c;b%=c;
    while(b)
    {
        if(b&1) ret=(ret+a)%c;
        a<<=1;
        if(a>=c) a%=c;
        b>>=1;
    }
    return ret;
}
ll pow_mod(ll x,ll n,ll m)
{
    if(n==1) return x%m;
    x%=m;
    ll ret=1;
    while(n)
    {
        if(n&1) ret=mul_mod(ret,x,m);
        x=mul_mod(x,x,m);
        n>>=1;
    }
    return ret;
}
bool check(ll a,ll n,ll x,ll t)
{
    ll ret=pow_mod(a,x,n);
    ll last=ret;
    for(ll i=1;i<=t;++i)
    {
        ret=mul_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1)
            return true;
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}
bool Miller_Rabin(ll n)
{
    if(n<2) return false;
    if(n==2) return true;
    if(!(n&1)) return false;
    ll x=n-1;
    ll t=0;
    while(!(x&1)) {x>>=1;t++;}
    for(int i=0;i<Maxt;++i)
    {
        ll a=rand()%(n-1)+1;
        if(check(a,n,x,t))
            return false;
    }
    return true;
}
bool solve(int b,int N)
{
    ll n=0;
    for(int i=0;i<N;++i)
    {
        n*=b;
        n+=1;
    }
    return Miller_Rabin(n);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int b,N;
    while(cin>>b>>N)
    {
        if(solve(b,N))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
