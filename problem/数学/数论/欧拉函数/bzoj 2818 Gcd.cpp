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
const int maxn=10000000+10;
bool flag[maxn];
int primes[maxn],pcnt;
ll phi[maxn];
void Init()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i]) primes[pcnt++]=i;
        for(int j=0;(j<pcnt) && (i*primes[j]<maxn);++j)
        {
            flag[i*primes[j]]=true;
            if (i%primes[j]==0) break;
        }
    }
}
ll solve(int n)
{
    phi[0]=phi[1]=0;
    for(int i=2;i<=n;++i) phi[i]=i;
    for(int i=2;i<=n;++i)
    {
        if(phi[i]==i)
        for(int j=i;j<=n;j+=i)
            phi[j]=phi[j]-phi[j]/i;
    }
    for(int i=1;i<maxn;++i) phi[i]+=phi[i-1];
    ll ans=0;
    for(int i=0;i<pcnt&&primes[i]<n;++i)
    {
        ans+=1+(phi[n/primes[i]]<<1);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n;
    cin>>n;
    cout<<solve(n)<<endl;
    return 0;
}
