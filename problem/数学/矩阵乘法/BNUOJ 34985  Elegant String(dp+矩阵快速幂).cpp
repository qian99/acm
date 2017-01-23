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
const int mod=20140518;
struct Matrix
{
    ll mat[11][11];
    int n;
    void clear() {memset(mat,0,sizeof(mat));}
    void Init(int n)
    {
        this->n=n;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=(i==j);
    }
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    c.n=a.n;
    for(int k=1;k<=c.n;++k)
        for(int i=1;i<=c.n;++i)
            for(int j=1;j<=c.n;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
ll cal(ll n,int k)
{
    Matrix x,y;
    x.Init(k);
    y.n=k;y.clear();
    for(int i=1;i<=k;++i)
        for(int j=1;j<=k;++j)
            y.mat[i][j]=(i>=j);
    for(int i=2;i<=k;++i)
        y.mat[i-1][i]=(k+1)-(i-1);
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x.mat[1][1]*(k+1)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        ll n,k;
        cin>>n>>k;
        cout<<"Case #"<<tcase<<": "<<cal(n,k)<<endl;
    }
    return 0;
}
