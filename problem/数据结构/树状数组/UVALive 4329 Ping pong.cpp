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
typedef long long ll;
const int maxn=100000+10;
ll C[maxn],ci[maxn],di[maxn],num[maxn];
int lowbit(int x)
{
    return x&-x;
}
ll sum(int x)
{
    ll ret=0;
    while(x>0)
    {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int x,int v,ll n)
{
    while(x<=n)
    {
        C[x]+=v;
        x+=lowbit(x);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ll res=0;
        ll maxnum=0;
        for(int i=1;i<=n;++i)
        {
            cin>>num[i];
            maxnum=max(maxnum,num[i]);
        }
        memset(C,0,sizeof(C));
        for(int i=1;i<=n;++i)
        {
            add(num[i],1,maxnum);
            ci[i]=sum(num[i])-1;
        }
        memset(C,0,sizeof(C));
        for(int i=n;i>=1;--i)
        {
            add(num[i],1,maxnum);
            di[i]=sum(num[i])-1;
        }
        for(int i=1;i<=n;++i)
        {
            res+=ci[i]*(n-i-di[i])+di[i]*(i-1-ci[i]);
        }
        cout<<res<<endl;
    }
    return 0;
}
