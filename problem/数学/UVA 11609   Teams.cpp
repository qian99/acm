#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int mod=1000000007;
ll f(int n)
{
    if(n==0) return 1;
    if(n==1) return 2;
    ll res=f(n/2);
    if(n%2==0)
        return (res*res)%mod;
    else
        return (((res*res)%mod)*2)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>n;
        ll ans=(n*f(n-1))%mod;
        cout<<"Case #"<<tcase<<": "<<ans<<endl;
    }
    return 0;
}
