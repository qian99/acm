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
const int maxn=500+10;
int primes[maxn],pcnt;
bool flag[maxn];
int v[maxn][maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(int j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
void div(int *v,int n)
{
    for(int i=0;i<pcnt;++i)
    {
        while(n%primes[i]==0)
        {
            v[i]++;
            n/=primes[i];
        }
    }
}
void Init()
{
    memset(v,0,sizeof(v));
    for(int i=2;i<maxn;++i)
        for(int j=i;j>1;--j)
            div(v[i],j);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    Init();
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        ll ans=1;
        for(int i=0;i<pcnt;++i)
            if(v[n][i]-v[n-k][i]-v[k][i]) ans*=(v[n][i]-v[n-k][i]-v[k][i]+1);
        printf("%lld\n",ans);
    }
    return 0;
}
