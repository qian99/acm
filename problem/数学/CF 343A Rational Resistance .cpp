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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b;
    cin>>a>>b;
    ll ans=0;
    ans+=a/b;
    a%=b;
    while(a!=0)
    {
        swap(a,b);
        ans+=a/b;
        a%=b;
    }
    cout<<ans<<endl;
    return 0;
}