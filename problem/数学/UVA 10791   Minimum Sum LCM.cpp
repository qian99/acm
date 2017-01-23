#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
//const int mod=1000000007;
ll solve(ll n)
{
    int lim=sqrt((double)(n+0.5));
    ll sum=0;
    ll tmp;
    int j=0;
    for(int i=2;i<=lim&&n>1;++i)
    {
        if(n%i==0&&n>1)
        {
            j++;
            tmp=1;
            while(n%i==0)
            {
                tmp*=i;
                n/=i;
            }
            sum+=tmp;
        }
    }
    if(n>1) sum+=n;
    if(j==1) sum++;
    if(j==0) return -1;
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    int t=0;
    while(cin>>n)
    {
        if(n==0) break;
        t++;
        ll res=solve(n);
        if(res<0) res=n+1;
        cout<<"Case "<<t<<": "<<res<<endl;
    }
    return 0;
}
