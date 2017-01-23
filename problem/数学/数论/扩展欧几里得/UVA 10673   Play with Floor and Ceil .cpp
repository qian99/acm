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
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll x,k,a,b,X,Y,d;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>x>>k;
        a=floor((double)x/k);
        b=ceil((double)x/k);
        d=ext_gcd(a,b,X,Y);
        X=X*(x/d);
        Y=Y*(x/d);
        cout<<X<<" "<<Y<<endl;
    }
    return 0;
}
