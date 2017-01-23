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
ll mod;
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
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
ll cal(ll a,ll b,ll n)
{
    double tmp=a+sqrt((double)b);
    if(n==2) tmp*=tmp;
    ll res=ceil(tmp);
    return res%mod;
}
ll solve(ll a,ll b,ll n)
{
    if(n<=2) return cal(a,b,n);
    n-=2;
    ll tmp1=cal(a,b,1),tmp2=cal(a,b,2);
    Matrix x,y;
    x.Init();y.clear();
    ll v=(b-a*a)%mod;
    y.mat[0][0]=2*a%mod;y.mat[1][0]=v;
    y.mat[0][1]=1;y.mat[1][1]=0;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return ((tmp2*x.mat[0][0]+tmp1*x.mat[1][0])%mod+mod)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b,n;
    while(cin>>a>>b>>n>>mod)
    {
        cout<<solve(a,b,n)<<endl;
    }
    return 0;
}
