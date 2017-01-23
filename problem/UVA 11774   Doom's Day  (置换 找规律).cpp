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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    while(t--)
    {
        ll x,y;
        cin>>x>>y;
        cout<<"Case "<<++tcase<<": "<<(x+y)/gcd(x,y)<<endl;
    }
    return 0;
}
