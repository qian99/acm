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
const int mod=10007;
struct Matrix
{
    int mat[4][4];
    void Init()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<4;++k)
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
int solve(int a,int b,int n)
{
    if(n==0) return 1;
    if(n==1) return 2;
    n-=1;
    Matrix x,y;
    x.Init();y.clear();
    y.mat[0][0]=y.mat[1][2]=1;
    y.mat[1][0]=y.mat[1][1]=(a*a)%mod;y.mat[2][0]=y.mat[2][1]=(b*b)%mod;
    y.mat[3][0]=y.mat[3][1]=(2*a*b)%mod;
    y.mat[1][3]=a;y.mat[3][3]=b;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return (x.mat[0][0]*2+x.mat[1][0]+x.mat[2][0]+x.mat[3][0])%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,x,y;
    while(~scanf("%d%d%d",&n,&x,&y))
    {
        printf("%d\n",solve(x%mod,y%mod,n));
    }
    return 0;
}
