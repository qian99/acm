#include <iostream>
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
ll gettimes(ll n)
{
    if(n==1) return 0;
    ll k=n%2;
    return gettimes(n/2+k)+1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        ll n,m,k;
        scanf("%I64d%I64d%I64d",&n,&m,&k);
        ll a=(n-1)+n*(m-1)+n*m*(k-1);
        ll b=gettimes(n)+gettimes(m)+gettimes(k);
        printf("Case #%d: %I64d %I64d\n",tcase,a,b);
    }
    return 0;
}
