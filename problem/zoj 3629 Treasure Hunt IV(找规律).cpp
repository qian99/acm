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
const ll maxz=(1ULL<<63)-1;
ll cal(ll n)
{
    if(n<0) return 0;
    ll m=(sqrt(n+0.0)+eps);
    ll sum=0;
    if(m%2==0) sum+=n-m*m+1,m--;
    sum+=(m+1)*m/2;
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b;
    while(cin>>a>>b)
    {
        cout<<cal(b)-cal(a-1)<<endl;
    }
    return 0;
}
