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
const int maxn = 1000+10;
struct Matrix
{
    int mat[10][10],n;
    void Init(int n)
    {
        this->n = n;
        for(int i = 0;i < n;++i)
            for(int j = 0; j < n;++j)
                mat[i][j] = (i==j);
    }
    void clear() { memset(mat,0,sizeof(mat));}
};
Matrix operator * (Matrix a,Matrix b)
{
    Matrix c;
    c.Init(a.n);
    c.clear();
    for(int k = 0;k < c.n;++k)
        for(int i = 0;i < c.n;++i)
            for(int j = 0;j < c.n;++j)
            {
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k]*b.mat[k][j])%6;
            }
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
int A[maxn][10],B[10][maxn],C[maxn][10],D[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,K;
    while(~scanf("%d%d",&n,&K))
    {
        if(n==0 && K==0) break;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < K;++j)
                scanf("%d",&A[i][j]);
        for(int i = 0;i < K;++i)
            for(int j = 0;j < n;++j)
                scanf("%d",&B[i][j]);
        Matrix a;
        a.Init(K);
        a.clear();
        for(int k = 0;k < n; ++k)
            for(int i = 0;i < K;++i)
                for(int j = 0;j < K;++j)
                    a.mat[i][j] = (a.mat[i][j] + B[i][k]*A[k][j])%6;
        a = pow_mat(a,n*n - 1);
        memset(C,0,sizeof(C));
        memset(D,0,sizeof(D));
        for(int k = 0;k < K ;++k)
            for(int i = 0;i < n;++i)
                for(int j = 0;j < K;++j)
                    C[i][j] = (C[i][j] + A[i][k]*a.mat[k][j])%6;
        for(int k = 0;k < K ;++k)
            for(int i = 0;i < n;++i)
                for(int j = 0;j < n;++j)
                    D[i][j] = (D[i][j] + C[i][k]*B[k][j])%6;
        int ans = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                ans += D[i][j];
        printf("%d\n",ans);
    }
    return 0;
}
