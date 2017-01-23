/*
* this code is made by qian99
* Problem: 1116
* Verdict: Accepted
* Submission Date: 2014-06-10 09:18:14
* Time: 644 MS
* Memory: 4900 KB
*/
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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
typedef unsigned long long Ull;
const int maxn=100000+10;
const int mod=1000000007;
const int mx=233;
Ull H[maxn],p[maxn];
char str[maxn];
int n;
ll val[maxn],sum[maxn];
inline bool check(int a,int b,int len)
{
    return H[a]-H[a+len]*p[len]==H[b]-H[b+len]*p[len];
}
int cal(int p)
{
    int l=1,r=n-p+1;
    if(!check(0,p,1)) return 0;
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        if(check(0,p,mid)) l=mid;
        else r=mid;
    }
    return l;
}
struct Matrix
{
    ll mat[2][2];
    void clear() {memset(mat,0,sizeof(mat));}
    void Init()
    {
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                mat[i][j]=(i==j);
    }
};
Matrix operator *(const Matrix &a ,const Matrix & b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
ll fibo(ll n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    n-=1;
    Matrix x,y;
    x.Init();
    y.mat[0][0]=y.mat[1][0]=y.mat[0][1]=1;
    y.mat[1][1]=0;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x.mat[0][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*mx;
    while(~scanf("%s",str))
    {
        n=strlen(str);
        H[n]=0;
        for(int i=n-1;i>=0;--i)
            H[i]=H[i+1]*mx+str[i];
        ll ans=0;
        for(int i=0;i<n;++i)
            val[i]=cal(i);
        sum[n]=0;
        for(int i=n-1;i>=0;--i)
        {
            sum[i]=sum[i+1]+val[i];
            ans=(ans+fibo(sum[i]))%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}