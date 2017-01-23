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
const int mod=7;
const char md[7][15]={"Saturday","Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
int c[50];
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
    c[0]=0;
    for(int i=1;i<=42;++i)
    {
        c[i]=pow_mod(i,i);
        c[i]+=c[i-1];
        c[i]%=7;
    }
    ll n;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ll m=n/42;
        ll res=m%mod*c[42]%mod;
        ll k=n%42;
        res+=c[k];
        res%=mod;
        cout<<md[res]<<endl;
    }
    return 0;
}

