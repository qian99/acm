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
    int mat[3][3];
    void Init()
    {
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
int n,m;
Matrix operator *(Matrix a,Matrix b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
int slove(ll n)
{
    if(n==0) return 0;
    n*=2;n-=1;
    Matrix p,q;
    p.Init();
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            q.mat[i][j]=1;
    q.mat[1][1]=0;
    while(n)
    {
        if(n&1) p=p*q;
        q=q*q;
        n>>=1;
    }
    return p.mat[0][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        printf("%d\n",slove(n));
    }
    return 0;
}
