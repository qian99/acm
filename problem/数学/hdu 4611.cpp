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
typedef long long ll;
ll gcd(ll a,ll b)
{
    ll c;
    while(b!=0)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
void slove(ll A,ll B,ll lcm,ll r,ll &once,ll &rval)
{
    ll a=0,b=0,c;
    ll temp;
    while(lcm)
    {
        temp=abs(a-b);
        c=min(A-a,B-b);
        once+=c*temp;
        lcm-=c;
        a=(a+c)%A;
        b=(b+c)%B;
        if(r>0)
        {
            if(r-c>0)
            {
                rval+=c*temp;
                r-=c;
            }
            else
            {
                rval+=temp*r;
                r=0;
            }
        }

    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    ll N,A,B;
    while(t--)
    {
        cin>>N>>A>>B;
        ll lcm=(A*B)/gcd(A,B);
        ll r=N%lcm;
        ll times=N/lcm;
        ll once=0,rval=0;
        slove(A,B,lcm,r,once,rval);
        ll ans=once*times+rval;
        cout<<ans<<endl;
    }
    return 0;
}
