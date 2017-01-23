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
const int maxn=300+10;
int mat[maxn][maxn];
ll sum[maxn][maxn],Sqsum[maxn][maxn];
int d[maxn][maxn][10];
int Log[maxn][maxn];
void Init_Rmq(int x,int n)
{
    Log[x][0]=-1;
    for(int i=1;i<=n;++i) Log[x][i]=(i&(i-1))?Log[x][i-1]:Log[x][i-1]+1;
    for(int i=1;i<=n;++i) d[x][i][0]=mat[x][i];
    for(int i=1;i<=Log[x][n];++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            d[x][j][i]=max(d[x][j][i-1],d[x][j+(1<<(i-1))][i-1]);
}
int RMQ(int x,int L,int R)
{
    int t=Log[x][R-L+1];
    return max(d[x][L][t],d[x][R-(1<<t)+1][t]);
}
double cal(int i,int j,int a,int b,int maxv)
{
    double res=0,x,x2;
    x=sum[i+a-1][j+b-1]-sum[i-1][j+b-1]-sum[i+a-1][j-1]+sum[i-1][j-1];
    x-=maxv;
    x/=(a*b-1);
    x2=x;
    x=x*x*(a*b-1);
    res=x;
    res+=Sqsum[i+a-1][j+b-1]-Sqsum[i-1][j+b-1]-Sqsum[i+a-1][j-1]+Sqsum[i-1][j-1]-maxv*maxv;
    x=sum[i+a-1][j+b-1]-sum[i-1][j+b-1]-sum[i+a-1][j-1]+sum[i-1][j-1]-maxv;
    x=x*x2*2;
    res-=x;
    return res/(a*b-1);
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,q,tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&mat[i][j]);
        for(int i=0;i<=n;++i) sum[i][0]=Sqsum[i][0]=0;
        for(int i=0;i<=m;++i) sum[0][i]=Sqsum[0][i]=0;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+mat[i][j];
                Sqsum[i][j]=Sqsum[i][j-1]+Sqsum[i-1][j]-Sqsum[i-1][j-1]+mat[i][j]*mat[i][j];
            }
        for(int i=1;i<=n;++i) Init_Rmq(i,m);
        scanf("%d",&q);
        int sx,sy,a,b,maxv;
        double minv,tmp;
        printf("Case %d:\n",++tcase);
        while(q--)
        {
            minv=1e10;
            scanf("%d%d",&a,&b);
            if(a==1&&b==1)
            {
                printf("(1, 1), 0.00\n");
                continue;
            }
            for(int i=1;i<=n-a+1;++i)
                for(int j=1;j<=m-b+1;++j)
                {
                    maxv=-1;
                    for(int k=i;k<i+a;++k)
                        maxv=max(maxv,RMQ(k,j,j+b-1));
                    tmp=cal(i,j,a,b,maxv);
                    if(dcmp(tmp-minv)<0)
                    {
                        minv=tmp;
                        sx=i;
                        sy=j;
                    }
                }
            printf("(%d, %d), %.2lf\n",sx,sy,minv);
        }
    }
    return 0;
}
