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
typedef unsigned long long Ull;
const int maxn=100000+10;
const int hval=233;
char strA[maxn],strB[maxn];
Ull p[maxn],HA[maxn],HB[maxn];
int n,m;
inline bool check(int x,int y,int len)
{
    return HA[x]-HA[x+len]*p[len]==HB[y]-HB[y+len]*p[len];
}
int lcp(int x,int y)
{
    int l=1,r=min(n-x,m-y)+1;
    if(!check(x,y,1)) return 0;
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        if(check(x,y,mid)) l=mid;
        else r=mid;
    }
    return l;
}
bool cal(int x)
{
    int totlen=0,tmp;
    tmp=lcp(x,0);
    totlen+=tmp;
    if(totlen+1>=m) return true;
    if(x+totlen+1>=n) return false;
    totlen++;
    tmp=lcp(x+totlen,totlen);
    totlen+=tmp;
    if(totlen+1>=m) return true;
    if(x+totlen+1>=n) return false;
    totlen++;
    tmp=lcp(x+totlen,totlen);
    return totlen+tmp>=m;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*hval;
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",strA);
        scanf("%s",strB);
        n=strlen(strA);
        m=strlen(strB);
        HA[n]=HB[m]=0;
        for(int i=n-1;i>=0;--i) HA[i]=HA[i+1]*hval+strA[i];
        for(int i=m-1;i>=0;--i) HB[i]=HB[i+1]*hval+strB[i];
        int ans=-1;
        for(int i=0;i<=n-m;++i)
            if(cal(i)) {ans=i;break;}
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}
