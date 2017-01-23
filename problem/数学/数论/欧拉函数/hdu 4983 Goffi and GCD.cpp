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
const int mod = 1000000000+7;
const int maxn = 40000+10;
int primes[maxn],phi[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    pcnt = 0;
    memset(flag,0,sizeof(flag));
    for(int i = 2;i < maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++] = i;
            for(int j = i*i;j <maxn;++j)
                flag[j] = true;
        }
    }
}
void phi_table()
{
    phi[1]=0;
    for(int i=2;i<maxn;++i) phi[i]=i;
    for(int i=2;i<maxn;++i)
    {
        if(phi[i]==i)
        {
            phi[i]=i-1;
            for(int j=i*2;j<maxn;j+=i)
                phi[j]=phi[j]-phi[j]/i;
        }
    }
    phi[1] = 1;
}
//int euler_phi(int n)
//{
//    int ans=n;
//    for(int i = 0;i < pcnt && n <= primes[i];++i)
//    {
//        if(n % primes[i] == 0)
//        {
//            ans = ans - ans/primes[i];
//            while(n%primes[i] == 0) n/=primes[i];
//        }
//    }
//    if(n>1) ans=ans-ans/n;
//    return ans;
//}
int euler_phi(int n)
{
    int m=sqrt(n+0.5);
    int ans=n;
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
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    getprimes();
    phi_table();
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        if(k > 2)
        {
            if(n == 1) puts("1");
            else puts("0");
            continue;
        }
        if(k == 2)
        {
            puts("1");
            continue;
        }
        ll res = 0;
        for(int i = 1;i*i <= n;++i)
        {
            if(n % i == 0)
            {
                if(n/i < maxn)
                {
                    if(i*i != n)
                        res =(res + (ll)phi[i]*phi[n/i]*2LL)%mod;
                    else
                        res =(res + (ll)phi[i]*phi[n/i])%mod;
                }
                else
                {
                    if(i*i != n)
                        res = (res + (ll)phi[i]*euler_phi(n/i)*2LL)%mod;
                    else
                        res =(res + (ll)phi[i]*phi[n/i])%mod;
                }
            }
        }
        printf("%I64d\n",res);
    }
    return 0;
}