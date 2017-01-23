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
const int mod=10000;
struct Matrix
{
    int mat[3][3];
    void Init()
    {
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(Matrix & a,Matrix & b)
{
    Matrix res;res.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                res.mat[i][j]=(res.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return res;
}
int solve(ll n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    n-=1;
    Matrix a,b;
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            a.mat[i][j]=1;
    a.mat[1][1]=0;b.Init();
    while(n)
    {
        if(n&1) b=a*b;
        a=a*a;
        n>>=1;
    }
    return b.mat[0][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    while(cin>>n)
    {
        if(n==-1) break;
        cout<<solve(n)<<endl;
    }
    return 0;
}
