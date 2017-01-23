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
bool flag[maxn]={0};
int primes[maxn];
int p;
void fp()
{
    int i,j;
    p=0;
 for(i=2;i<maxn;++i)
 {
  if(!flag[i])
  {
   primes[p++]=i;
  }
  for(j=0;(j<p) && (i*primes[j]<maxn);++j)
  {
   flag[i*primes[j]]=true;
   if (i % primes[j] == 0)
               break;
  }
 }
}
ll solve(ll G,ll L)
{
    ll res=1;
    int c1,c2;
    for(int i=0;primes[i]*primes[i]<=L;++i)
    {
        if(L%primes[i]==0)
        {
        c1=c2=0;
        while(L%primes[i]==0) {c2++;L/=primes[i];}
        while(G%primes[i]==0) {c1++;G/=primes[i];}
        if(c1==c2)
         continue;
        else if(c1+1==c2)
         res*=6;
        else
         res*=((ll)(c2-c1-1)*6+6);
        }
    }
    if(L>1&&G==1) res*=6;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    fp();
    int t;
    cin>>t;
    while(t--)
    {
        ll G,L;
        cin>>G>>L;
        if(L%G!=0)
        {
            cout<<0<<endl;
            continue;
        }
        cout<<solve(G,L)<<endl;
    }
    return 0;
}
