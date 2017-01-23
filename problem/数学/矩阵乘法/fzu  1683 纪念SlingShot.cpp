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
const int mod=2009;
struct Matrix
{
    int mat[4][4];
    void Init()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
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
int solve(int n)
{
    if(n==0) return 1;
    if(n==1) return 4;
    n-=2;
    Matrix x,y;
    x.Init();y.clear();
    y.mat[0][0]=y.mat[1][2]=y.mat[2][3]=1;
    y.mat[1][0]=y.mat[1][1]=3;
    y.mat[2][0]=y.mat[2][1]=2;
    y.mat[3][0]=y.mat[3][1]=7;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    int ans=9*x.mat[0][0]+5*x.mat[1][0]+3*x.mat[2][0]+x.mat[3][0];
    return ans%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        printf("Case %d: %d\n",tcase,solve(n));
    }
    return 0;
}
