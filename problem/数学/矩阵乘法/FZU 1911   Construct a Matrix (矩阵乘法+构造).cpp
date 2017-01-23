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
int mod;
struct Matrix
{
    int mat[4][4];
    void Init()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<4;++k)
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
int getFibo(int n)
{
    if(n==1) return 1;
    if(n==2) return 2;
    Matrix x,y;
    x.Init();
    y.clear();
    y.mat[0][0]=y.mat[0][1]=y.mat[0][2]=1;
    y.mat[1][0]=y.mat[1][3]=y.mat[2][2]=y.mat[3][3]=1;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    return x.mat[0][2]%mod;
}
int a[220][220];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&mod);
        int m=getFibo(n)%mod;
        printf("Case %d: ",tcase);
        if((m&1)||m==0) puts("No");
        else
        {
            puts("Yes");
            int k=m/2;
            memset(a,0,sizeof(a));
            for(int i=0;i<k;++i)
                for(int j=0;j<k;++j)
                {
                    if(i+j>=k) a[i][j]=1;
                    a[i][j+k]=1;
                    a[i+k][j]=-1;
                    if(i+j>=k-1) a[i+k][j+k]=-1;
                }
            if(m==2)
            {
                a[0][0]=-1;
                a[0][1]=1;a[1][0]=0;
                a[1][1]=1;
            }
            for(int i=0;i<m;++i)
            {
                for(int j=0;j<m;++j)
                {
                    if(j) printf(" ");
                    printf("%d",a[i][j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
