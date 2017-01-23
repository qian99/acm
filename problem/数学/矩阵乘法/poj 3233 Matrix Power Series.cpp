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
const int maxn=31;
struct Matrix
{
    int mat[maxn][maxn],n;
    Matrix(){};
    Matrix(int nn) {n=nn;}
    void Init()
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
int n,m,k;
Matrix operator *(const Matrix &a ,const Matrix & b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
Matrix operator +(const Matrix &a,const Matrix & b)
{
    Matrix c(a.n);
    for(int i=0;i<c.n;++i)
        for(int j=0;j<c.n;++j)
            c.mat[i][j]=(a.mat[i][j]+b.mat[i][j])%m;
    return c;
}
Matrix p(const Matrix & a,int N)
{
    Matrix x=(n),y=a;
    x.Init();
    while(N)
    {
        if(N&1) x=x*y;
        y=y*y;
        N>>=1;
    }
    return x;
}
Matrix f(const Matrix &a,int N)
{
    Matrix c(a.n);
    c.Init();
    if(N==0) return c;
    if(N==1) return c=a;
    if(N&1) return f(a,N-1)+p(a,N);
    return f(a,N/2)*(p(a,N/2)+c);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&k,&m);
    Matrix a(n);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            scanf("%d",&a.mat[i][j]);
            a.mat[i][j]%=m;
        }
    Matrix ans=f(a,k);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(j) printf(" ");
            printf("%d",ans.mat[i][j]%m);
        }
        printf("\n");
    }
    return 0;
}
