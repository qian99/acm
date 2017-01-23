#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll k,p;
    while(cin>>k>>p)
    {
        ll x=k/(p-1);
        if(x&1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
