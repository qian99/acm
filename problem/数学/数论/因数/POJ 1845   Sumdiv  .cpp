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
const int maxn=20000+10;
const int mod=9901;
ll primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(int j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
ll pow_mod(ll a,ll n)
{
    ll res=1;
    a%=mod;
    while(n)
    {
        if(n&1) res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
ll pow_sum(ll p,ll n)
{
    if(n==0) return 1;
    if(n&1) return pow_sum(p,n/2)*(1+pow_mod(p,n/2+1))%mod;
    return (pow_sum(p,n/2-1)*(1+pow_mod(p,n/2+1))+pow_mod(p,n/2))%mod;
}
ll solve(ll A,ll B)
{
    ll tot;
    ll ans=1;
    for(int i=0;i<pcnt;++i)
    {
        if(A%primes[i]==0)
        {
            tot=0;
            while(A%primes[i]==0) {A/=primes[i];tot++;}
            ans=ans*(pow_sum(primes[i],B*tot))%mod;
        }
    }
    if(A>1)
    {
        ans=ans*(pow_sum(A,B))%mod;
    }
    return (ans+mod)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    ll A,B;
    while(cin>>A>>B)
    {
        if(A==0) cout<<"0"<<endl;
        else cout<<solve(A,B)<<endl;
    }
    return 0;
}
