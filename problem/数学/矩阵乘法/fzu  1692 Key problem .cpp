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
    ll mat[maxn][maxn];
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
int mod,L,R,n,m;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c(a.n);c.clear();
    for(int k=0;k<c.n;++k)
        for(int j=0;j<c.n;++j)
            c.mat[0][j]=(c.mat[0][j]+a.mat[0][k]*b.mat[k][j])%mod;
    for(int i=1;i<c.n;++i)
    {
        c.mat[i][0]=c.mat[i-1][c.n-1];
        for(int j=1;j<c.n;++j)
            c.mat[i][j]=c.mat[i-1][j-1];
    }
    return c;
}
int num[maxn];
void solve()
{
    swap(L,R);
    Matrix x(n),y(n);
    x.Init();y.clear();
    for(int i=1;i<n-1;++i)
    {
        y.mat[i][i]=1;
        y.mat[i-1][i]=L;
        y.mat[i+1][i]=R;
    }
    y.mat[1][0]=y.mat[0][n-1]=R;
    y.mat[n-1][0]=y.mat[n-2][n-1]=L;
    y.mat[0][0]=y.mat[n-1][n-1]=1;
    while(m)
    {
        if(m&1) x=x*y;
        y=y*y;
        m>>=1;
    }
    ll ans=0;
    for(int i=0;i<n;++i)
    {
        if(i) printf(" ");
        ans=0;
        for(int j=0;j<n;++j)
            ans=(ans+x.mat[j][i]*num[j])%mod;
        printf("%I64d",ans);
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&m,&L,&R,&mod);
        for(int i=0;i<n;++i)
            scanf("%d",&num[i]);
        solve();
    }
    return 0;
}
