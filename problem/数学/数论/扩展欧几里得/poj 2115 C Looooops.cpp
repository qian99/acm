#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
    ll A,B,C,k,x,y,a,b,c,d;
    while(cin>>A>>B>>C>>k)
    {
        if(A==0&&B==0&&C==0&&k==0) break;
        k=(1LL)<<k;
        a=C;b=k;c=B-A;
        d=ext_gcd(a,b,x,y);
        if(c%d!=0)
            cout<<"FOREVER"<<endl;
        else
        {
            c/=d;x*=c;b/=d;
            x=(x%b+b)%b;
            cout<<x<<endl;
        }
    }
    return 0;
}
