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
const int maxn=16;
struct Matrix
{
    int mat[maxn][maxn],n;
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
int m,num[maxn],val[maxn];
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
int solve(int d,int n)
{
    if(n<=d) return num[n]%m;
    n-=d;
    Matrix x(d),y(d);
    x.Init();y.clear();
    for(int i=0;i<d;++i)
    {
        y.mat[i][0]=val[i+1];
        if(i!=d-1) y.mat[i][i+1]=1;
    }
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    int ans=0;
    for(int i=0;i<d;++i)
        ans=(ans+x.mat[i][0]*num[d-i])%m;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int d,n;
    while(~scanf("%d%d%d",&d,&n,&m))
    {
        if(d==0&&n==0&&m==0) break;
        for(int i=1;i<=d;++i)
        {
            scanf("%d",&val[i]);
            val[i]%=m;
        }
        for(int i=1;i<=d;++i)
        {
            scanf("%d",&num[i]);
            num[i]%=m;
        }
        printf("%d\n",solve(d,n));
    }
    return 0;
}
