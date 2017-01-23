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
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
typedef long long ll;
const int maxn=33;
const ll mod=1234567891;
struct Matrix
{
    ll mat[maxn][maxn];
    int n;
    Matrix(){};
    Matrix(int nn){n=nn;}
    void Init()
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix operator +(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);
    for(int i=0;i<c.n;++i)
        for(int j=0;j<c.n;++j)
            c.mat[i][j]=(a.mat[i][j]+b.mat[i][j])%mod;
    return c;
}
Matrix p(const Matrix& a,ll n)
{
    Matrix x(a.n),y;x.Init();
    y=a;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x;
}
Matrix f(const Matrix& a,ll n)
{
    Matrix c(a.n);
    if(n==1) return c=a;
    if(n&1) return f(a,n-1)+p(a,n);
    c.Init();
    return f(a,n/2)*(p(a,n/2)+c);
}
ll solve(ll n,int k)
{
    if(n==1) return k;
    Matrix x(k),y(k);
    y.clear();
    for(int i=0;i<k;++i)
    {
        y.mat[i][i]=k-i;
        if(i!=k-1) y.mat[i+1][i]=i+1;
    }
    x=f(y,n-1);
    return ((x.mat[k-1][0]+(k==1))*k)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,k;
    ll n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%I64d%d",&n,&k);
        printf("%I64d\n",solve(n,k));
    }
    return 0;
}
