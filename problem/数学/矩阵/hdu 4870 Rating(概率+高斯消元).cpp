#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
const int maxn=220;
double A[maxn][maxn],p;
int id[maxn][maxn];
void guass(int n)
{
    int i,j,k,r;
    for(i=0;i<n;++i)
    {
        r=i;
        for(j=i+1;j<n;++j)
            if(fabs(A[j][i])>fabs(A[r][i])) r=j;
        if(r!=i) for(j=0;j<=n;++j) swap(A[r][j],A[i][j]);

        for(k=i+1;k<n;++k)
        {
            double f=A[k][i]/A[i][i];
            for(j=i;j<=n;++j) A[k][j]-=f*A[i][j];
        }
    }
    for(i=n-1;i>=0;--i)
    {
        for(j=i+1;j<n;++j)
            A[i][n]-=A[j][n]*A[i][j];
        A[i][n]/=A[i][i];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n=0;
    for(int i=0;i<20;++i)
        for(int j=i;j<20;++j)
            id[i][j]=n++;
    while(~scanf("%lf",&p))
    {
        memset(A,0,sizeof(A));
        int x,y;
        for(int i=0;i<20;++i)
            for(int j=i;j<20;++j)
            {
                A[id[i][j]][id[i][j]]+=-1;
                A[id[i][j]][n]=-1;
                x=i+1;
                y=j;
                if(x>y) swap(x,y);
                if(y!=20)
                {
                    A[id[i][j]][id[x][y]]+=p;
                }
                x=i-2;y=j;
                if(x<0) x=0;
                A[id[i][j]][id[x][y]]+=(1-p);
            }
        guass(n);
        printf("%.6lf\n",A[0][n]);
    }
    return 0;
}
