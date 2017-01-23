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
int a[20],N;
int euler_phi(int n)
{
    int m=sqrt(n+0.5);
    int ans=n;
    for(int i=2;i<=m;++i)
    {
        if(n%i==0)
        {
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans=ans-ans/n;
    return ans;
}
int pow_mod(int x,int n,int m)
{
    int res=1,tmp=1;
    for(int i=0;i<n;++i)
    {
        tmp*=x;
        if(tmp>=m) break;
    }
    if(tmp>=m) tmp=m;
    else tmp=0;
    while(n)
    {
        if(n&1) res=res*x%m;
        x=x*x%m;
        n>>=1;
    }
    return res+tmp;
}
int solve(int p,int m)
{
    if(p==N-1)
    {
        if(a[p]>=m) return a[p]%m+m;
        return a[p];
    }
    int c=euler_phi(m);
    int k=solve(p+1,c);
    int ans=pow_mod(a[p],k,m);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int M,tcase=0;
    char str[10];
    while(~scanf("%s",str))
    {
        if(str[0]=='#') break;
        tcase++;
        M=0;
        int len=strlen(str);
        for(int i=0;i<len;++i)
            M=M*10+(str[i]-'0');
        scanf("%d",&N);
        for(int i=0;i<N;++i)
            scanf("%d",&a[i]);
        printf("Case #%d: %d\n",tcase,solve(0,M)%M);
    }
    return 0;
}
