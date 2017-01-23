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
using namespace std;
typedef long long ll;
const int maxn=501;
struct Matrix
{
    int mat[maxn][maxn];
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
int n,m,k,d;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int j=0;j<c.n;++j)
            c.mat[0][j]=(c.mat[0][j]+(ll)a.mat[0][k]*b.mat[k][j])%m;
    for(int i=1;i<c.n;++i)
    {
        c.mat[i][0]=c.mat[i-1][c.n-1];
        for(int j=1;j<c.n;++j)
            c.mat[i][j]=c.mat[i-1][j-1];
    }
    return c;
}
ll num[maxn];
Matrix x,y;
void solve(int n,int k)
{
    x.n=n;y.n=n;
    x.Init();y.clear();
    y.mat[0][0]=1;
    for(int i=1;i<=d;++i)
        y.mat[i][0]=y.mat[n-i][0]=1;
    for(int j=1;j<n;++j)
    {
        y.mat[0][j]=y.mat[n-1][j-1];
        for(int i=1;i<n;++i)
            y.mat[i][j]=y.mat[i-1][j-1];
    }
    while(k)
    {
        if(k&1) x=x*y;
        y=y*y;
        k>>=1;
    }
    ll ans;
    for(int i=0;i<n;++i)
    {
        if(i) printf(" ");
        ans=0;
        for(int j=0;j<n;++j)
            ans=(ans+num[j]*x.mat[j][i])%m;
        printf("%lld",ans);
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d%d",&n,&m,&d,&k))
    {
        for(int i=0;i<n;++i)
            scanf("%lld",&num[i]);
        solve(n,k);
    }
    return 0;
}
