#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
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
    double mat[2][2];
    void Init()
    {
        mat[0][0]=mat[1][1]=1;
        mat[0][1]=mat[1][0]=0;
    }
    void clear() {memset(mat,0,sizeof(mat));}
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
int mines[20];
void cal(int n,double &p1,double &p2,double p)
{
    Matrix x,y;
    x.Init();y.clear();
    y.mat[0][0]=p;y.mat[1][0]=1-p;
    y.mat[0][1]=1;
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    double px=p1*x.mat[0][0]+p2*x.mat[1][0];
    double py=p1*x.mat[0][1]+p2*x.mat[1][1];
    p1=px;p2=py;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    double p;
    while(~scanf("%d%lf",&n,&p))
    {
        for(int i=0;i<n;++i)
            scanf("%d",&mines[i]);
        sort(mines,mines+n);
        double ans=0,p1,p2;
        if(mines[0]!=1)
        {
            p1=1,p2=0;
            int now=1;
            for(int i=0;i<n;++i)
            {
                cal(mines[i]-now,p1,p2,p);
                p1=0;
                now=mines[i];
            }
            ans=(1-p)*p2;
        }
        printf("%.7lf\n",ans);
    }
    return 0;
}
