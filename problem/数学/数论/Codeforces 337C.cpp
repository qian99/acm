#include <iostream>
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
typedef __int64 ll;
const ll mod=1000000000+9;
ll p(ll n)
{
    if(n==0) return 1;
    if(n==1) return 2;
    ll tmp=p(n/2);
    tmp=(tmp*tmp)%mod;
    if(n%2) return (tmp*2)%mod;
    return tmp%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m,k;
    while(cin>>n>>m>>k)
    {
        ll wa=n-m;
        ll z=wa*k;
        ll res,tmp;
        if(z>=n)
          res=m%mod;
        else
        {
            res=((k-1)*wa)%mod;
            z=n-z;
            tmp=z/k;
            ll mmm=((p(tmp+1)-2)%mod+mod)%mod;
            res=res+(mmm*k)%mod+z%k;
            res%=mod;
        }
        cout<<res<<endl;
    }
    return 0;
}