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
const int maxn=100000+10;
bool check(ll a,ll b,ll c,ll n)
{
    ll m=n/3;
    return a>=0&&b>=0&&c>=0&&a<=m&&b<=m&&c<=m;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,k,d1,d2;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>k>>d1>>d2;
        if(n%3!=0)
        {
            cout<<"no"<<endl;
            continue;
        }
        ll a,b,c,tmp;
        tmp=k-d1+d2;
        if(tmp>=0&&tmp%3==0)
        {
            b=tmp/3;
            a=d1+b;
            c=b-d2;
            if(check(a,b,c,n))
            {
                cout<<"yes"<<endl;
                continue;
            }
        }
        tmp=k-d1-d2;
        if(tmp>=0&&tmp%3==0)
        {
            b=tmp/3;
            a=b+d1;
            c=b+d2;
            if(check(a,b,c,n))
            {
                cout<<"yes"<<endl;
                continue;
            }
        }
        tmp=k+d1+d2;
        if(tmp>=0&&tmp%3==0)
        {
            b=tmp/3;
            a=b-d1;
            c=b-d2;
            if(check(a,b,c,n))
            {
                cout<<"yes"<<endl;
                continue;
            }
        }
        tmp=k+d1-d2;
        if(tmp>=0&&tmp%3==0)
        {
            b=tmp/3;
            a=b-d1;
            c=b+d2;
            if(check(a,b,c,n))
            {
                cout<<"yes"<<endl;
                continue;
            }
        }
        cout<<"no"<<endl;
    }
    return 0;
}