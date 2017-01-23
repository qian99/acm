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
ll check(ll x)
{
    ll cnt=0;
    while(x)
    {
        cnt+=x/5;
        x/=5;
    }
    return cnt;
}
ll f(ll x)
{
    ll L=0,R=x;
    ll m,tmp;
    while(L<R)
    {
        m=(L+R)>>1;
        tmp=check(m*5);
        if(tmp==x) return m*5;
        if(tmp<x)
           L=m+1;
        else
           R=m;
    }
    tmp=check(L*5);
    if(tmp==x) return L*5;
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    //5 10 15 20 25 30  40 45  50  55  60...50 75 100 125 150 1
    //1  2  3  4 6   7  8   9  11  12
    ll q,ans;
    cin>>q;
    if(q==0)
    {
        cout<<1<<endl;
        return 0;
    }
    ans=f(q);
    if(ans==-1) cout<<"No Solution"<<endl;
    else cout<<ans<<endl;
    return 0;
}
