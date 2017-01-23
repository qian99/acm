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
const int maxn=1000000+10;
char str1[maxn],str2[maxn];
ll cnt[30],m,n;
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
ll lcm(int a,int b)
{
    return (ll)a*b/gcd(a,b);
}
ll solve(const char *s1,int len1,const char *s2,int len2)
{
    ll ret=0,cp;
    int p=gcd(len1,len2);
    cp=len2/p;
    for(int i=0;i<p;++i)
    {
        memset(cnt,0,sizeof(cnt));
        for(int j=i;j<len2;j+=p)
          cnt[s2[j]-'a']++;
        for(int j=i;j<len1;j+=p)
          ret+=(cp-cnt[s1[j]-'a']);
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%I64d%I64d",&n,&m))
    {
        scanf("%s",str1);
        scanf("%s",str2);
        int len1=strlen(str1);
        int len2=strlen(str2);
        ll res;
        if(len1>=len2)
          res=solve(str1,len1,str2,len2);
        else res=solve(str2,len2,str1,len1);
        ll tmp=n*len1;
        tmp=tmp/lcm(len1,len2);
        res=res*tmp;
        printf("%I64d\n",res);
    }
    return 0;
}
