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
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll p[15];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,k,res,res2;
    while(cin>>n>>k)
    {
        p[0]=1;
        for(int i=1;i<=n;++i) p[i]=p[i-1]*k;
        res=res2=0;
        for(int i=0;i<n;++i) res+=p[gcd(n,i)];
        res2=res;
        if(n&1) res2+=p[(n-1)/2+1]*n;
        else res2+=p[n/2]*(n/2)+p[n/2+1]*(n/2);
        cout<<res/n<<" "<<res2/(2*n)<<endl;
    }
    return 0;
}

