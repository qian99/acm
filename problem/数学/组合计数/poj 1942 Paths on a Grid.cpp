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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m;
    while(cin>>n>>m)
    {
        if(n==0&&m==0) break;
        if(n>m) swap(n,m);
        ll N=n+m,ans=1;
        for(ll i=1;i<=n;++i)
        {
            ans*=(N-i+1);
            ans/=i;
        }
        cout<<ans<<endl;
    }
    return 0;
}
