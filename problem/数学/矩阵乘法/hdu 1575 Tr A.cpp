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
const int mod=9973;
struct Matrix
{
    int mat[10][10],n;
    Matrix(){};
    Matrix(int nn) {n=nn;}
    void Init()
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(Matrix a,Matrix b)
{
    Matrix c(a.n);
    c.clear();
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
int solve(int n,int k)
{
    Matrix p(n),q(n);
    p.Init();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            scanf("%d",&q.mat[i][j]);
    while(k)
    {
        if(k&1) p=p*q;
        q=q*q;
        k>>=1;
    }
    int ans=0;
    for(int i=0;i<n;++i)
        ans=(ans+p.mat[i][i])%mod;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        printf("%d\n",solve(n,k));
    }
    return 0;
}
