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
const int maxm=50000+10;
const int maxn=5000+10;
int a[maxn],g[maxn];
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int primes[maxm],pcnt,n,m;
bool flag[maxm];
map<int,int>mp;
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxm;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=(ll)i*i;j<maxm;j+=i)
                flag[j]=true;
        }
    }
}
int getval(int v)
{
    int res=0;
    int M=sqrt(v+0.5);
    for(int i=0;i<pcnt&&primes[i]<=M;++i)
    {
        if(v%primes[i]==0)
        {
            int add=mp[primes[i]]?-1:1;
            while(v%primes[i]==0)
            {
                v/=primes[i];
                res+=add;
            }
        }
    }
    if(v>1) res+=mp[v]?-1:1;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)
        scanf("%d",&a[i]);
    int tmp;
    for(int i=0;i<m;++i)
    {
        scanf("%d",&tmp);
        mp[tmp]=1;
    }
    g[0]=a[0];
    for(int i=1;i<n;++i)
        g[i]=gcd(a[i],g[i-1]);
    int r=n-1;
    while(r>=0)
    {
        tmp=getval(g[r]);
        if(tmp<=0)
        {
            int x=g[r];
            for(int i=r;i>=0;--i)
            {
                g[i]/=x;
                a[i]/=x;
            }
        }
        r--;
    }
    int ans=0;
    for(int i=0;i<n;++i)
        ans+=getval(a[i]);
    printf("%d\n",ans);
    return 0;
}