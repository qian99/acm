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
typedef  __int64 ll;
const ll mod=1000000000+7;
const int maxn=100000+10;
char num[maxn];
ll pp(ll n)
{
    if(n==0) return 1;
    if(n==1) return 2;
    ll tmp=pp(n/2);
    tmp=(tmp*tmp)%mod;
    if(n&1) return (tmp*2)%mod;
    return tmp;
}
ll getNum(int len)
{
    ll p=1;
    ll x,res=0;
    int jw=-1;
    for(int i=len-1;i>=0;--i)
    {
        x=num[i]-'0'+jw;
        if(x<0) x=9;
        else jw=0;
        x*=p;
        res+=x;
        res%=(mod-1);
        p*=10;
        p%=(mod-1);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",num))
    {
        int len=strlen(num);
        ll n=getNum(len);
        printf("%I64d\n",pp(n));
    }
    return 0;
}
