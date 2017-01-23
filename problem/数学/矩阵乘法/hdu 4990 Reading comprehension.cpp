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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
struct Matrix
{
    ll mat[2][2];
    void Init()
    {
        for(int i = 0;i < 2;++i)
            for(int j = 0;j < 2;++j)
                mat[i][j] = (i == j);
    }
    void clear()
    {
        memset(mat,0,sizeof(mat));
    }
};
ll n,m;
Matrix operator * (const Matrix a,const Matrix b)
{
    Matrix c;
    c.clear();
    for(int k = 0;k < 2;++k)
        for(int i = 0;i < 2;++i)
            for(int j = 0;j < 2;++j)
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
Matrix pow_mat(Matrix a,ll N)
{
    Matrix res;
    res.Init();
    while(N)
    {
        if(N & 1) res = res*a;
        a = a*a;
        N >>= 1;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Matrix x;
    x.mat[0][0] = 4;
    x.mat[1][0] = x.mat[1][1] = 1;
    x.mat[0][1] = 0;
    while(~scanf("%I64d%I64d",&n,&m))
    {
        Matrix res;
        ll ans;
        if(n & 1)
        {
            res = pow_mat(x,(n+1)/2 - 1);
            ans = res.mat[0][0] + res.mat[1][0];
            ans %= m;
        }
        else
        {
            res = pow_mat(x,n/2 - 1);
            ans = res.mat[0][0]*2 + res.mat[1][0]*2;
            ans %= m;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}