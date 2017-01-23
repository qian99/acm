#include <iostream>
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
const int mod=1000000000+7;
typedef long long ll;
ll pw(int n)
{
    if(n==0) return 1;
    if(n==1) return 2;
    ll tmp=pw(n/2);
    if(n%2) return (tmp*tmp*2)%mod;
    else return (tmp*tmp)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    int n,k;
    while(t--)
    {
        cin>>n>>k;
        if(n<k) cout<<"0"<<endl;
        else if(n==k) cout<<"1"<<endl;
        else if(n==k+1) cout<<"2"<<endl;
        else
        {
            int m=n-k-2;
            ll res=n-k+3;
            res=res*(pw(m)%mod);
            res%=mod;
            cout<<res<<endl;
        }
    }
    return 0;
}
