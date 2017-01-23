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
const int maxn=105;
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
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])&1;
    return c;
}
char str[maxn];
void solve(int n,int m)
{
    Matrix x(n),y(n);
    x.Init();y.clear();
    for(int i=1;i<n;++i)
        y.mat[i][i]=y.mat[i-1][i]=1;
    y.mat[0][0]=y.mat[n-1][0]=1;
    while(m)
    {
        if(m&1) x=x*y;
        y=y*y;
        m>>=1;
    }
    for(int i=0;i<n;++i)
    {
        int ans=0;
        for(int j=0;j<n;++j)
            ans=(ans+(str[j]-'0')*x.mat[j][i])&1;
        printf("%d",ans);
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&m))
    {
        scanf("%s",str);
        n=strlen(str);
        solve(n,m);
    }
    return 0;
}
