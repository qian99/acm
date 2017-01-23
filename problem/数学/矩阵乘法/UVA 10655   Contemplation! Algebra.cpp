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
struct Matrix
{
    ll mat[2][2];
    void Init()
    {
        mat[0][0]=mat[1][1]=1;
        mat[1][0]=mat[0][1]=0;
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
    return c;
}
ll p,q,n;
ll solve(ll n)
{
    if(n==0) return 2;
    if(n==1) return p;
    if(n==2) return p*p-2*q;
    n-=2;
    Matrix x,y;
    x.Init();y.clear();
    y.mat[0][0]=p;y.mat[0][1]=1;
    y.mat[1][0]=-q;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x.mat[0][0]*(p*p-2*q)+x.mat[1][0]*p;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>p>>q>>n)
    {
//        if(p==0&&q==0) break;
//        scanf("%lld",&n);
        cout<<solve(n)<<endl;
//        printf("%lld\n",solve(n));
    }
    return 0;
}
