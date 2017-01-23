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
const int maxn=2000+10;
int n,m,k;
double p1,p2,p3,p4,p5,p6,p7;
double dp[maxn][maxn],c[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d%lf%lf%lf%lf",&n,&m,&k,&p1,&p2,&p3,&p4))
    {
        if((p4==0)||(1-p1-p4<eps))
          printf("0.00000\n");
        else
        {
            p5=p2/(1-p1);p6=p3/(1-p1);p7=p4/(1-p1);
            dp[1][1]=p4/(1-p1-p2);c[1]=p7;c[2]=p6*dp[1][1]+(2<=k?p7:0);
            double a,b;
            for(int i=2;i<=n;++i)
            {
                a=p5;b=c[2];
                for(int j=2;j<=i;++j)
                {
                    a=a*p5;b=p5*b+c[(j==i?1:j+1)];
                }
                dp[i][1]=b/(1-a);
                for(int j=2;j<=i;++j)
                  dp[i][j]=p5*dp[i][j-1]+c[j];
                for(int j=2;j<=i+1;++j)
                  c[j]=p6*dp[i][j-1]+(j<=k?p7:0);
            }
            printf("%.5lf\n",dp[n][m]);
        }
    }
    return 0;
}
