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
ll cal(ll n)
{
    ll lg=log2(n);
    if((1LL<<lg)==n)
    {
        return n/2*lg+n;
    }
    return cal(1LL<<lg)+cal(n^(1LL<<lg));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    while(cin>>n)
    {
        cout<<cal(n)<<endl;
    }
    return 0;
}