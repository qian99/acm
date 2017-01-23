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
const int mod=1000000007;
struct Matrix
{
    ll mat[10][10];
    int n;
    void clear() {memset(mat,0,sizeof(mat));}
    void Init(int n)
    {
        this->n=n;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=(i==j);
    }
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    c.n=a.n;
    for(int k=1;k<=c.n;++k)
        for(int i=1;i<=c.n;++i)
            for(int j=1;j<=c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix operator +(const Matrix &a,const Matrix &b)
{
    Matrix c;c.n=a.n;
    c.clear();
    for(int i=1;i<=c.n;++i)
        for(int j=1;j<=c.n;++j)
            c.mat[i][j]=(a.mat[i][j]+b.mat[i][j])%mod;
    return c;
}
Matrix create(int n)
{
    Matrix x;
    x.n=n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            x.mat[i][j]=(i!=j);
    if(n==6)
    {
        x.mat[1][6]=x.mat[2][4]=x.mat[3][5]=0;
        x.mat[6][1]=x.mat[4][2]=x.mat[5][3]=0;
    }
    else if(n==8)
    {
        x.clear();
        x.mat[1][2]=x.mat[1][4]=x.mat[1][5]=1;
        x.mat[2][1]=x.mat[2][3]=x.mat[2][6]=1;
        x.mat[3][2]=x.mat[3][4]=x.mat[3][7]=1;
        x.mat[4][1]=x.mat[4][3]=x.mat[4][8]=1;
        x.mat[5][1]=x.mat[5][6]=x.mat[5][8]=1;
        x.mat[6][2]=x.mat[6][5]=x.mat[6][7]=1;
        x.mat[7][3]=x.mat[7][6]=x.mat[7][8]=1;
        x.mat[8][4]=x.mat[8][5]=x.mat[8][7]=1;
    }
    return x;
}
Matrix p(const Matrix& a,ll n)
{
    Matrix x,y;
    x.Init(a.n);
    y=a;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x;
}
void ptmat(Matrix x)
{
    for(int i=1;i<=x.n;++i)
    {
        for(int j=1;j<=x.n;++j)
            cout<<x.mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
Matrix f(const Matrix& a,ll n)
{
    Matrix c;c.n=a.n;
    if(n==1) return c=a;
    if(n&1) return f(a,n-1)+p(a,n);
    c.Init(a.n);
//    ptmat(f(a,n/2));
//    ptmat(p(a,n/2));
//    ptmat(p(a,n/2)+c);
//    ptmat(f(a,n/2)*(p(a,n/2)+c));
    return f(a,n/2)*(p(a,n/2)+c);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,n,s,t;
    ll K;
    cin>>T;
    while(T--)
    {
        cin>>n>>K>>s>>t;
        Matrix x,y;
        if(n==6) n=8;
        else if(n==8) n=6;
        x.Init(n);
        y=create(n);
        x=f(y,K);
//        x=f(y,1)*(p(y,1)+x);
//        ptmat(x);
        cout<<x.mat[s][t]<<endl;
    }
    return 0;
}
