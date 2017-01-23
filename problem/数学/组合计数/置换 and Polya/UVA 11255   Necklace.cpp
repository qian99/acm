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
const int maxn=44;
int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }
ll C[maxn][maxn];
int a,b,c;
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
}
ll cal(int a,int b,int c,int len,int tot)
{
    ll res=0,tmp;
    if(a%len==0&&b%len==0&&c%len==0)
    {
        tmp=C[tot][a/len];
        tot-=a/len;
        tmp*=C[tot][b/len];
        res+=tmp;
    }
    return res;
}
ll solve()
{
    ll ans=0;
    int n=a+b+c,num,len;
    for(int i=0;i<n;++i)
    {
        num=gcd(n,i);
        len=n/num;
        ans+=cal(a,b,c,len,num);
    }
    if(n&1)
    {
        if(a) ans+=cal(a-1,b,c,2,(n-1)/2)*n;
        if(b) ans+=cal(a,b-1,c,2,(n-1)/2)*n;
        if(c) ans+=cal(a,b,c-1,2,(n-1)/2)*n;
    }
    else
    {
        ans+=(n/2)*cal(a,b,c,2,n/2);
        int aa,bb,cc;
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
            {
                aa=a;bb=b;cc=c;
                if(i==0) aa--;
                else if(i==1) bb--;
                else cc--;
                if(j==0) aa--;
                else if(j==1) bb--;
                else cc--;
                if(aa<0||bb<0||cc<0) continue;
                ans+=(n/2)*cal(aa,bb,cc,2,(n-2)/2);
            }
    }
    return ans/(2*n);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&a,&b,&c);
        ll ans=solve();
        printf("%lld\n",ans);
    }
    return 0;
}
