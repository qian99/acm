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
const int C=201;
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll random(ll n)
{
    return (ll)((double)rand()/RAND_MAX*n+0.5);
}
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
bool Witness(ll a,ll n)
{
    ll m=n-1;
    int j=0;
    while(!(m&1)) {j++;m>>=1;}
    ll x=pow_mod(a,m,n);
    if(x==1||x==n-1) return false;
    while(j--)
    {
        x=x*x%n;
        if(x==n-1) return false;
    }
    return true;
}
bool Miller_Rabin(ll n)
{
    if(n<2) return false;
    if(n==2) return true;
    if(!(n&1)) return false;
    for(int i=0;i<Maxt;++i)
    {
        ll a=random(n-2)+1;
        if(Witness(a,n)) return  false;
    }
    return true;
}
//注意调用前要将tot赋值为0
ll factor[550],tot;
ll Pollard_rho(ll n,int c)
{
    ll x,y,d,i=1,k=2;
    x=random(n-1)+1;
    y=x;
    while(true)
    {
        i++;
        x=(mul_mod(x,x,n)+c)%n;
        d=gcd(y-x,n);
        if(1<d&&d<n) return d;
        if(y==x) return n;
        if(i==k)
        {
            y=x;
            k<<=1;
        }
    }
}
void findfac(ll n,int k)
{
    if(n==1) return ;
    if(Miller_Rabin(n))
    {
        factor[tot++]=n;
        return;
    }
    ll p=n;
    while(p>=n) p=Pollard_rho(p,k--);
    findfac(p,k);
    findfac(n/p,k);
}
ll num[610],numcnt[650],mina,minb,mins,lcmv,gcdv,val;
void dfs(int pos,ll a)
{
    if(pos==(int)tot)
    {
        ll b=val/a;
        if(gcd(a,b)==1)
        {
            a*=gcdv;
            b*=gcdv;
            if(a+b<mins)
            {
                mins=a+b;
                mina=min(a,b);
                minb=max(a,b);
            }
        }
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=(int)numcnt[pos];++i)
    {
        if(tmp*a>=mins) return;
        dfs(pos+1,a*tmp);
        tmp*=num[pos];
    }
}
void solve()
{
    if(lcmv==gcdv)
    {
        mina=minb=gcdv;
        return ;
    }
    tot=0;
    val=lcmv/gcdv;
    findfac(val,C);
    sort(factor,factor+tot);
    memset(numcnt,0,sizeof(numcnt));
    int cnt=1;
    num[0]=factor[0];numcnt[0]=1;
    for(int i=1;i<(int)tot;++i)
    {
        if(factor[i]!=num[cnt-1])
            num[cnt++]=factor[i];
        numcnt[cnt-1]++;
    }
    tot=cnt;
    mins=(1ULL<<63)-1;
    dfs(0,1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>gcdv>>lcmv)
    {
        solve();
        cout<<mina<<" "<<minb<<endl;
    }
    return 0;
}
