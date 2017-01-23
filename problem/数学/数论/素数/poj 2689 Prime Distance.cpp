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
const int maxn=65536+100;
const int maxm=1000000+100;
int primes[maxn],pcnt;
ll minl,minr,maxl,maxr;
bool flag[maxn],vis[maxm];
void getprimes()
{
    pcnt=0;
    memset(flag,0,sizeof(flag));
    for(ll i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
void solve(ll L,ll R)
{
    ll minv=inf,maxv=0,len=R-L+1;
    minl=minr=maxl=maxr=-1;
    memset(vis,0,sizeof(vis));
    ll j;
    for(int i=0;i<pcnt;++i)
    {
        j=L/primes[i];
        while(j*primes[i]<L||j<=1) j++;
        for(ll k=j*primes[i];k<=R;k+=primes[i])
            vis[k-L]=true;
    }
    if(L==1) vis[0]=true;
    ll pre=-1;
    for(int i=0;i<len;++i)
    {
        if(vis[i]) continue;
        if(pre==-1) pre=i;
        else
        {
            ll tmp=i-pre;
            if(tmp<minv)
            {
                minv=tmp;
                minl=L+pre;
                minr=L+i;
            }
            if(tmp>maxv)
            {
                maxv=tmp;
                maxl=L+pre;
                maxr=L+i;
            }
            pre=i;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    ll L,R;
    while(~scanf("%lld%lld",&L,&R))
    {
        solve(L,R);
        if(minl==-1)
            printf("There are no adjacent primes.\n");
        else
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n",minl,minr,maxl,maxr);
    }
    return 0;
}
