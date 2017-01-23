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
const int maxn=100000+10;
int primes[maxn],pcnt;
bool flag[maxn];
int p[10000100];
void getprimes()
{
    pcnt=0;
    memset(flag,0,sizeof(flag));
    flag[0]=flag[1]=true;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=(ll)i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
bool check(int n)
{
    if(n<maxn) return !flag[n];
    for(int i=0;i<pcnt&&(ll)primes[i]*primes[i]<n;++i)
        if(n%primes[i]==0) return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b,k,s;
        scanf("%d%d%d%d",&a,&b,&k,&s);
        int ans=0,cnt=0;
        for(int i=a;i<=b;++i)
        {
            if(check(i))
                p[cnt++]=i;
        }
        for(int i=0;i<=cnt-k;++i)
        {
            if(p[i+k-1]-p[i]==s)
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
