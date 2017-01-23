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
    int mat[4][4];
    void init()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                mat[i][j]=(i==j);
    }
    void clear(){memset(mat,0,sizeof(mat));}
};
int m;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<4;++k)
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
    return c;
}
int solve(int n)
{
    if(n==0) return 0;
    if(n==1) return 2%m;
    if(n==2) return 4%m;
    Matrix x,y;
    x.init();y.clear();
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
        {
            if((i&1)!=(j>>1)) continue;
            int st=(i<<1)|j;
            if(st!=0&&st!=2)
                y.mat[i][j]=1;
        }
    n-=2;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    int ans=0;
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            ans=(ans+x.mat[i][j])%m;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int L;
    while(~scanf("%d%d",&L,&m))
    {
        printf("%d\n",solve(L));
    }
    return 0;
}
