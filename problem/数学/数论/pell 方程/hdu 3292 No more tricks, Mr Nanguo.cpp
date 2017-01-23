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
const int mod=8191;
struct Matrix
{
    ll mat[2][2];
    void Init()
    {
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix & a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
void find(ll N,ll &X,ll &Y)
{
    ll x,y=1,z;
    while(true)
    {
        x=N*y*y+1;
        z=sqrt((double)x);
        if(z*z==x) {X=z,Y=y;return;}
        y++;
    }
}
ll solve(ll N,ll K)
{
    ll x1,y1;
    find(N,x1,y1);
    if(K==1) return x1;
    K-=1;
    Matrix a,b;
    a.Init();b.clear();
    b.mat[0][0]=b.mat[1][1]=x1;
    b.mat[1][0]=N*y1;b.mat[0][1]=y1;
    while(K)
    {
        if(K&1) a=a*b;
        b=b*b;
        K>>=1;
    }
    return (x1*a.mat[0][0]+y1*a.mat[1][0])%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll N,K;
    while(cin>>N>>K)
    {
        if(N==4||N==9||N==16||N==25)
            cout<<"No answers can meet such conditions"<<endl;
        else
            cout<<solve(N,K)<<endl;
    }
    return 0;
}
