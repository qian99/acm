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
ll n,rr,kk,minval;
ll counts(ll k,ll r,ll N)
{
    ll res=1;
    for(int i=1;i<=r+1;++i)
     res*=k;
    res=(res-1);
    if(res%(k-1))
    {
        if(res/(k-1)==N) return res/(k-1)+1;
    }
    return res/(k-1);
}
void solve(ll r,ll N)
{
    ll L=2,R=(ll)(pow(n,1.0/r)+1+eps);
    ll m,tmp;
    while(L<R)
    {
        m=(L+R)>>1;
        tmp=counts(m,r,N);
        if(tmp>N)
          R=m-1;
        else if(tmp<N)
          L=m+1;
        else
        {
            L=m;
            break;
        }
    }
    if(counts(L,r,N)==N)
    {
        if(minval>r*L)
        {
            minval=r*L;
            rr=r;kk=L;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%I64d",&n))
    {
        minval=1*(n-1);
        rr=1;kk=n-1;
        for(int i=2;i<=45;++i)
        {
            solve(i,n);
            solve(i,n+1);
        }
        printf("%I64d %I64d\n",rr,kk);
    }
    return 0;
}
