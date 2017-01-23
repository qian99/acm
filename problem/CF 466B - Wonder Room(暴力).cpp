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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll n,a,b;
    cin>>n>>a>>b;
    if(a*b < 6*n)
    {
        bool flag = false;
        if(a > b) {swap(a,b);flag = true;}
        ll l = a, r = sqrt(6*n + 0.5),j,x;
        x = b;
        b = 6*n/a + 1;
        for(ll i = l;i <= r;++i)
        {
            j = 6*n/i;
            if(i*j < 6*n) j++;
            if(j >= x && i*j < a*b)
            {
                a = i;
                b = j;
            }
        }
        if(flag) swap(a,b);
    }
    cout<<a*b<<endl;
    cout<<a<<" "<<b<<endl;
    return 0;
}