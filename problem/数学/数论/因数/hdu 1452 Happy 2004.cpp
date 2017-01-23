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
const int mod=29;
int ext_gcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    int d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int inv(int a)
{
    int x,y;
    ext_gcd(a,mod,x,y);
    return (x%mod+mod)%mod;
}
int pow_mod(int a,int n)
{
    int res=1;
    a%=mod;
    while(n)
    {
        if(n&1) res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
int cal(int p,int n)
{
    int k=inv(p-1);
    return (pow_mod(p,n+1)-1)*k%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x;
    while(~scanf("%d",&x))
    {
        if(x==0) break;
        int ans=0;
        ans=cal(2,2*x)*cal(3,x)*cal(167,x)%mod;
        printf("%d\n",ans%mod);
    }
    return 0;
}
