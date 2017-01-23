#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=85;
const int mod=1000000007;
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
Matrix operator *(const Matrix& a,const Matrix & b)
{
    Matrix c(a.n);
    c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
ll C[55][55],p[55],num[maxn];
void Init()
{
    memset(C,0,sizeof(C));
    p[0]=1;
    for(int i=1;i<=50;++i)
        p[i]=(p[i-1]*2)%mod;
    for(int i=0;i<=50;++i)
        C[i][0]=1,C[i][1]=i;
    for(int i=1;i<=50;++i)
    {
        for(int j=2;j<=i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
}
ll solve(ll n,int k)
{
    if(n==1) return 1;
    if(n==2) return (p[k+1]+1)%mod;
    ll sum=0;
    int nn=2*k+3;
    num[0]=p[k+1]+1;
    num[1]=2;num[k+2]=1;
    for(int i=1;i<=k;++i)
    {
        num[i+1]=2*p[i];
        num[i+k+2]=1;
    }
    Matrix x(nn),y(nn);
    x.Init(); y.clear();
    y.mat[0][0]=1;
    y.mat[1][1]=y.mat[k+2][1]=1;
    for(int i=0;i<=k;++i)
    {
        y.mat[i+1][0]=C[k][i];
        y.mat[i+k+2][0]=(C[k][i]*p[k-i])%mod;
        y.mat[i+1][i+k+2]=1;
    }
    for(int i=0;i<=k;++i)
    {
        for(int j=0;j<=i;++j)
        {
            y.mat[j+1][i+1]=C[i][j];
            y.mat[j+k+2][i+1]=(C[i][j]*p[i-j])%mod;
        }
    }
    n-=2;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    for(int i=0;i<nn;++i)
        sum=(sum+num[i]*x.mat[i][0])%mod;
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    int k;
    Init();
    while(cin>>n>>k)
    {
        cout<<solve(n,k)<<endl;
    }
    return 0;
}
