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
ll cal(ll n,ll k)
{
    if(n-1<k) return 0;
    ll l=1,r=n+1,m;
    while(r-l>1)
    {
        m=(l+r)>>1;
        if(n/m>=k+1) l=m;
        else r=m;
    }
    return l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m,k;
    cin>>n>>m>>k;
    if(n+m-2<k)
    {
        cout<<-1<<endl;
    }
    else
    {
        ll ans=0;
        if(k<=n-1) ans=max(ans,cal(n,k)*m);
        else ans=max(ans,cal(m,k-n+1));
        if(k<=m-1) ans=max(ans,cal(m,k)*n);
        else ans=max(ans,cal(n,k-m+1));
        cout<<ans<<endl;
    }
    return 0;
}