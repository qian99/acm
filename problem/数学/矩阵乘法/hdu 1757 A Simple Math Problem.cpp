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
struct Matrix
{
    ll mat[11][11];
    void Init()
    {
        for(int i=0;i<10;++i)
            for(int j=0;j<10;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
int m;
ll num[20];
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<10;++k)
        for(int i=0;i<10;++i)
            for(int j=0;j<10;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
ll solve(ll n)
{
    if(n<10) return n;
    Matrix x,y;
    x.Init();y.clear();
    for(int i=0;i<10;++i)
    {
        y.mat[i][0]=num[i];
        if(i) y.mat[i-1][i]=1;
    }
    n-=9;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    ll ans=0;
    for(int i=0;i<10;++i)
        ans=(ans+x.mat[i][0]*(9-i))%m;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll k;
    while(~scanf("%I64d%d",&k,&m))
    {
        for(int i=0;i<10;++i)
            scanf("%I64d",&num[i]);
        printf("%I64d\n",solve(k));
    }
    return 0;
}
