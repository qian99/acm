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
    ll a,b,m,n,L,x,y;
    cin>>a>>b>>m>>n>>L;
    ll A=m-n,B=-L,C=b-a;
    ll d=ext_gcd(A,B,x,y);
    if(C%d!=0)
        cout<<"Impossible"<<endl;
    else
    {
        x=x*C/d;
        if(B<0) B=-B;
        x=(x%B+B)%B;
        cout<<x<<endl;
    }
    return 0;
}
