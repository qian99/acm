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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
bool issqrt(ll x)
{
    ll y=sqrt(x);
    return y*y==x;
}
bool check(ll M)
{
    ll C=(M-1)*2LL;
    if(!issqrt(1+4*C)) return false;
    C=sqrt(1+C*4)-1;
    if(C>0&&C%2==0) return true;
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    ll M;
    cin>>t;
    while(t--)
    {
        cin>>M;
        if(check(M)) puts("YES");
        else puts("NO");
    }
    return 0;
}
