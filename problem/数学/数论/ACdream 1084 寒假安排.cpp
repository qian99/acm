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
const int maxn=100000+10;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(ll i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
ll factor[maxn],num[maxn];
int tot;
void Fenjie(ll n)
{
    tot=0;
    for(int i=0;i<pcnt&&primes[i]<=n;++i)
    {
        if(n%primes[i]==0)
        {
            factor[tot]=primes[i];
            num[tot]=0;
            while(n%primes[i]==0) {n/=primes[i];num[tot]++;}
            tot++;
        }
    }
    if(n>1) {factor[tot]=n;num[tot++]=1;}
}
ll cal(ll n,ll m,ll p)
{
    ll val=p;
    ll sum=0;
    while(val<=n)
    {
        sum+=n/val-(n-m)/val;
        val*=p;
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t;
    ll m,n,k;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k;
        Fenjie(k);
        ll ans=cal(n,m,factor[0])/num[0];
        for(int i=1;i<tot;++i)
            ans=min(ans,cal(n,m,factor[i])/num[i]);
        cout<<ans<<endl;
    }
    return 0;
}
