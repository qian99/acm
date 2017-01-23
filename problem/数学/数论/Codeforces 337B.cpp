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
typedef __int64 ll;
ll gcd(ll a,ll b)
{
    ll c;
    while(b!=0)
    {
        c=b;
        b=a%b;
        a=c;
    }
    return a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b,c,d;
    while(cin>>a>>b>>c>>d)
    {
        ll mul=a*c/gcd(a,c);
        ll tmp=mul/a;
        a*=tmp;b*=tmp;
        tmp=mul/c;
        c*=tmp;d*=tmp;
        while(d>b)
        {
            swap(a,b);
            swap(c,d);
            mul=a*c/gcd(a,c);
            tmp=mul/a;
            a*=tmp;b*=tmp;
            tmp=mul/c;
            c*=tmp;d*=tmp;
        }
        ll p,q;
        if(a==c)
        {
            p=b-d;
            q=b;
        }
        else
        {
            p=a-c;
            q=a;
        }
        tmp=gcd(p,q);
        cout<<p/tmp<<"/"<<q/tmp<<endl;
    }
    return 0;
}