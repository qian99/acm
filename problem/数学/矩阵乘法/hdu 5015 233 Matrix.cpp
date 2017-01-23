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
const int mod = 10000007 ;
struct Matrix
{
    ll mat[15][15];
    int n;
    void Init(int n)
    {
        this->n = n;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                mat[i][j] = (i == j);
    }
    void clear()
    {
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                mat[i][j] = 0;
    }
};
Matrix operator * (const Matrix & a,const Matrix & b)
{
    Matrix c;
    c.clear();
    c.n = a.n;
    for(int k = 0;k < c.n;++k)
        for(int i = 0;i < c.n;++i)
            for(int j = 0;j < c.n;++j)
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix pow_mat(Matrix x,int n)
{
    Matrix res;
    res.Init(x.n);
    while(n)
    {
        if(n & 1) res = res*x;
        x = x*x;
        n >>= 1;
    }
    return res;
}
ll a[20];
void ptmat(Matrix x)
{
    int n = x.n;
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < n;++j)
            cout<<x.mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 0;i < n;++i)
        {
            scanf("%I64d",&a[i]);
            a[i] %= mod;
        }
        Matrix x;
        x.n = n + 2;
        x.clear();
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j <= i;++j)
                x.mat[j][i] = 1;
            x.mat[n][i] = 1;
        }
        x.mat[n][n] = 10;
        x.mat[n+1][n] = x.mat[n+1][n+1] = 1;
//        ptmat(x);
        x = pow_mat(x,m);
//        ptmat(x);
        a[n] = 233;
        a[n+1] = 3;
        ll ans = 0;
        for(int i = 0;i < n + 2;++i)
        {
            ans += x.mat[i][n-1]*a[i]%mod;
            if(ans >= mod) ans -= mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
