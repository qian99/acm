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
struct Node
{
    ll size,val;
};
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
ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    ll n;
    Node nx,ny,tmp;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%I64d%I64d%I64d%I64d%I64d",&n,&nx.size,&nx.val,&ny.size,&ny.val);
        if(nx.size<ny.size)
        {
            tmp=nx;
            nx=ny;
            ny=tmp;
        }
        ll res=0,ans=0,num,z,r;
        z=lcm(nx.size,ny.size);
        num=n/z;
        r=n%z;
        if(num)
        {
            num--;
            r+=z;
        }
        res=max(z/nx.size*num*nx.val,z/ny.size*num*ny.val);
        for(int i=0;i<=r/nx.size;++i)
        {
            ans=max(ans,i*nx.val+(r-i*nx.size)/ny.size*ny.val);
        }
        printf("Case #%d: %I64d\n",tcase,res+ans);
    }
    return 0;
}
