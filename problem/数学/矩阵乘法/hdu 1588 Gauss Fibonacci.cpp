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
struct Matrix
{
    ll mat[4][4];
    int n;
    Matrix(){}
    Matrix(int n):n(n){}
    void Init()
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
ll k,b,n,M;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%M;
    return c;
}
Matrix p(Matrix x,ll n)
{
    Matrix y(x.n);
    y.Init();
    while(n)
    {
        if(n&1) y=y*x;
        x=x*x;
        n>>=1;
    }
    return y;
}
ll solve()
{
    Matrix x(2),y(2),z(2),s(4);
    x.mat[0][0]=x.mat[0][1]=x.mat[1][0]=1;
    x.mat[1][1]=0;
    y=p(x,b);
    z=p(x,k);
    s.clear();
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            s.mat[i][j]=z.mat[i][j];
    s.mat[2][2]=s.mat[3][3]=s.mat[0][2]=s.mat[1][3]=1;
    s=p(s,n);
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            z.mat[i][j]=s.mat[i][j+2];
    x=y*z;
    return x.mat[1][0]%M;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>k>>b>>n>>M)
    {
        cout<<solve()<<endl;
    }
    return 0;
}
