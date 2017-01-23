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
int n,m;
ll k;
ll cal(ll val)
{
    ll sum=0;
    for(int i=1;i<=m;++i)
        sum+=min((ll)n,val/i);
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cin>>n>>m>>k;
    if(n<m) swap(n,m);
    ll L=1,R=(ll)n*m;
    while(L<R)
    {
        ll mid=(L+R)>>1;
        if(cal(mid)<k) L=mid+1;
        else R=mid;
    }
    cout<<L<<endl;
    return 0;
}
